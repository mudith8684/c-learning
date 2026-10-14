#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

struct Node {
    long long data;
    struct Node* next;
};

typedef struct Node* NODE;

NODE createNode (long long data) {
    NODE newNode = malloc (sizeof (struct Node));
    if (newNode == NULL) {
        printf("malloc failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int push (NODE *top, long long data) {
    NODE newNode = createNode(data);
    if (newNode == NULL) {
        return 0; // Failure
    }
    newNode->next = *top;
    *top = newNode;
    return 1; // Success
}

int pop (NODE *top, long long * value) {
    if (*top == NULL) {
        return 0; // Failure
    }
    NODE temp = *top;
    *value = temp->data;
    *top = temp->next;
    free(temp);
    return 1; // Success
}

int isEmpty (NODE top) {
    return top == NULL;
}

void freeStack (NODE *top) {
    long long value;
    while (pop(top, &value)) {
        // Free nodes without printing.
    }
}

int precedence (char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/':
        case '%': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

int appendChar (char output[], size_t capacity, size_t *length, char ch) {
    if (*length + 1 >= capacity) {
        return 0; // Failure
    }
    output[(*length)++] = ch;
    output[*length] = '\0';
    return 1; // Success
}

int infixToPostfix (const char infix[], char postfix[], size_t capacity) {
    NODE operators = NULL;
    size_t i = 0, j = 0;
    int expectOperand = 1;
    long long value;
    postfix[0] = '\0';
    while (infix[i] != '\0') {
        char ch = infix[i];
        if (isspace((unsigned char)ch)) {
            i++;
            continue;
        }
        if (isdigit((unsigned char)ch)) {
            if (!expectOperand) {
                printf("Error: missing operator.\n");
                goto failure;
            }
            while (isdigit((unsigned char)infix[i])) {
                if (!appendChar(postfix, capacity, &j, infix[i])) {
                    printf("Postfix output too long.\n");
                    goto failure;
                }
                i++;
            }
            if (!appendChar(postfix, capacity, &j, ' ')) {
                printf("Postfix output too long.\n");
                goto failure;
            }
            expectOperand = 0;
            continue;
        }
        if (ch == '(') {
            if (!expectOperand) {
                printf("Error: missing operator before '('.\n");
                goto failure;
            }
            if (!push(&operators, ch)) {
                goto failure;
            }
            i++;
            expectOperand = 1;
            continue;
        }
        if (ch == ')') {
            if (expectOperand) {
                printf("Error: misplaced ')'.\n");
                goto failure;
            }
            while (!isEmpty(operators) && operators->data != '(') {
                pop(&operators, &value);
                if (!appendChar(postfix, capacity, &j, (char)value) || 
                    !appendChar(postfix, capacity, &j, ' ')) {
                    printf("Postfix output too long.\n");
                    goto failure;
                }
            }
            if (isEmpty(operators)) {
                printf("Error: unmatched ')'.\n");
                goto failure;
            }
            pop(&operators, &value);
            i++;
            expectOperand = 0;
            continue;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^') {
            if (expectOperand) {
                printf("Error: operator in invalid position.\n");
                goto failure;
            }
            while (!isEmpty(operators) && operators->data != '(' && 
                (precedence((char)operators->data) > precedence(ch) || 
                precedence((char)operators->data) == precedence(ch) && ch != '^')) {
                pop(&operators, &value);
                if (!appendChar(postfix, capacity, &j, (char) value) || 
                    !appendChar(postfix, capacity, &j, ' ')) {
                    printf("Postfix output too long.\n");
                    goto failure;
                }
            }
            if (!push(&operators, ch)) {
                goto failure;
            }
            i++;
            expectOperand = 1;
            continue;
        }
        printf("Error: invalid character %c.\n", ch);
        goto failure;
    }
    if (expectOperand) {
        printf("Error: incomplete or empty expression.\n");
        goto failure;
    }
    while (!isEmpty(operators)) {
        pop(&operators, &value);
        if (value == '(') {
            printf("Error: unmatched '('.\n");
            goto failure;
        }
        if (!appendChar(postfix, capacity, &j, (char)value) || 
            !appendChar(postfix, capacity, &j, ' ')) {
            printf("Postfix output too long.\n");
            goto failure;
        }
    }
    freeStack(&operators);
    return 1;
failure:
    freeStack(&operators);
    postfix[0] = '\0';
    return 0;
}

int integerPower (long long base, long long exponent, long long *result) {
    if (exponent < 0) {
        printf("Error: negative exponents are not supported.\n");
        return 0;
    }
    *result = 1;
    while (exponent > 0) {
        if (exponent % 2 != 0) {
            *result *= base;
        }
        exponent /= 2;
        if (exponent > 0) {
            base *= base;
        }
    }
    return 1;
}

int evaluatePostfix (const char postfix[], long long *result) {
    NODE values = NULL;
    char expression[2048];
    char *token, *endptr;
    long long left, right, answer;
    if (strlen(postfix) >= sizeof(expression)) {
        printf("Error: postfix expression too long.\n");
        return 0;
    }
    strcpy(expression, postfix);
    token = strtok(expression, " \t\r\n");
    while (token != NULL) {
        if (isdigit((unsigned char)token[0])) {
            errno = 0;
            long long number = strtoll(token, &endptr, 10);
            if (errno == ERANGE || *endptr != '\0') {
                printf("Error: invalid number or out-of-range number.\n");
                goto failure;
            }
            if (!push(&values, number)) {
                goto failure;
            }
        } else if (strlen(token) == 1) {
            char op = token[0];
            if (!pop(&values, &right) || !pop(&values, &left)) {
                printf("Error: insufficient operands.\n");
                goto failure;
            }
            switch (op) {
                case '+': {
                    answer = left + right;
                    break;
                }
                case '-': {
                    answer = left - right;
                    break;
                }
                case '*': {
                    answer = left * right;
                    break;
                }
                case '/': {
                    if (right == 0) {
                        printf("Error: division by zero.\n");
                        goto failure;
                    }
                    answer = left / right;
                    break;
                }
                case '%': {
                    if (right == 0) {
                        printf("Error: modulo by zero.\n");
                        goto failure;
                    }
                    answer = left % right;
                    break;
                }
                case '^': {
                    if (!integerPower(left, right, &answer)) {
                        goto failure;
                    }
                    break;
                }
                default: {
                    goto failure;
                }
            }
            if (!push(&values, answer)) {
                goto failure;
            }
        } else {
            printf("Error: invalid postfix token.\n");
            goto failure;
        }
        token = strtok(NULL, " \t\r\n");
    }
    if (!pop(&values, result) || !isEmpty(values)) {
        printf("Error: invalid postfix expression.\n");
        goto failure;
    }
    freeStack(&values);
    return 1;
failure:
    freeStack(&values);
    return 0;
}

int main (void) {
    char infix[512], postfix[2048];
    long long result;
    printf("Enter an expression: ");
    if (fgets(infix, sizeof(infix), stdin) == NULL) {
        printf("Error reading expression.\n");
        return 1;
    }
    if (strchr(infix, '\n') == NULL && !feof(stdin)) {
        printf("Error: expression is too long.\n");
        return 1;
    }
    if (!infixToPostfix(infix, postfix, sizeof(postfix))) {
        printf("Error: unable to convert infix expression to postfix.\n");
        return 1;
    }
    if (!evaluatePostfix(postfix, &result)) {
        printf("Error: unable to evaluate postfix expression.\n");
        return 1;
    }
    printf("Evaluation result: %lld\n", result);
    return 0;
}