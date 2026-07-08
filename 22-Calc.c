#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

typedef double real_t;

// Binary operations
real_t add_(real_t a, real_t b);
real_t subtract_(real_t a, real_t b);
real_t multiply_(real_t a, real_t b);
real_t divide_(real_t a, real_t b);
real_t pow_(real_t base, long exp);

// Unary operations
real_t neg_(real_t );
real_t abs_(real_t a);
real_t sin_taylor(real_t a);
real_t cos_taylor(real_t a);

int needs_second_operand(char op) {
    switch (op) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return 1;

        case 'n':
        case 'a':
        case 's':
        case 'c':
            return 0;

        default:
            printf("Unsupported operation.\n");
            return -1;
    }
}

int main(void) {
    real_t a, b, result = 0.0;
    char op;

    printf("Enter a: ");
    if (scanf("%lf", &a) != 1) {
        printf("Invalid input for a.\n");
        return 1;
    }

    printf("Operator (supported: +, -, *, /, ^, negative(n), absolute(a), sin(s), cos(c)): ");
    if (scanf(" %c", &op) != 1) {
        printf("Failed to read operator.\n");
        return 1;
    }

    int need_b = needs_second_operand(op);
    if (need_b < 0) {
        return 1;
    }
    if (need_b) {
        printf("Enter b: ");
        if (scanf("%lf", &b) != 1) {
            printf("Invalid input for b.\n");
            return 1;
        }
    }

    switch (op) {
        case '+':
            result = add_(a, b);
            break;
        case '-':
            result = subtract_(a, b);
            break;
        case '*':
            result = multiply_(a, b);
            break;
        case '/':
            result = divide_(a, b);
            break;
        case '^':
            result = pow_(a, (long)b);
            printf("Note: Exponent truncated to integer.\n");
            break;
        case 'n':
            result = neg_(a);
            break;
        case 'a':
            result = abs_(a);
            break;
        case 's':
            result = sin_taylor(a);
            break;
        case 'c':
            result = cos_taylor(a);
            break;
        default:
            printf("Unknown operator.\n");
            return 1;
    }
    printf("Result = %lf\n", result);
    return 0;
}

real_t add_(real_t a, real_t b) {
    return a + b;
}

real_t subtract_(real_t a, real_t b) {
    return a - b;
}

real_t multiply_(real_t a, real_t b) {
    return a * b;
}

real_t divide_(real_t a, real_t b){
    if (b == 0.0){
        printf("Division by zero!\n");
        return 0.0;
    }
    return a / b;
}

real_t pow_(real_t base, long exp) {
    if (exp == 0)
        return 1.0;

    int neg = 0;
    if (exp < 0) {
        neg = 1;
        exp = -exp;
    }

    real_t result = 1.0;
    while (exp > 0) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }

    return neg ? 1.0 / result : result;
}

real_t neg_(real_t a) {
    return -a;
}

real_t abs_(real_t a) {
    return a < 0 ? -a : a;
}

real_t sin_taylor(real_t a) {
    while (a > PI)
        a -= 2 * PI;
    while (a < -PI)
        a += 2 * PI;

    real_t term = a;
    real_t sum = a;
    int n = 0;

    while (fabs(term) > 1e-12) {
        term *= -a * a / ((2*n + 2) * (2*n + 3));
        sum += term;
        n++;
    }

    return sum;
}

real_t cos_taylor(real_t a) {
    while (a > PI)
        a -= 2 * PI;
    while (a < -PI)
        a += 2 * PI;

    real_t term = 1.0;
    real_t sum  = 1.0;
    int n = 0;

    while (fabs(term) > 1e-12) {
        term *= -a * a / ((2*n + 1) * (2*n + 2));
        sum += term;
        n++;
    }

    return sum;
}
