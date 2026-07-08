#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

struct Student {
    int roll;
    char name[50];
    int attendedClasses;
    int totalClasses;
    float attendance;
    int marks[3];
    float avg;
    char grade;
};

void updateAttendance (struct Student s[], int n);
void displayStudents (struct Student s[], int n);
void shortageList (struct Student s[], int n);
void classTopper (struct Student s[], int n);

void calculateAverage(struct Student *s) {
    s->avg = (s->marks[0] + s->marks[1] + s->marks[2]) / 3.0;
}

void assignGrade (struct Student *s) {
    if (s->avg >= 90) {
        s->grade = 'A';
    } else if (s->avg >= 80) {
        s->grade = 'B';
    } else if (s->avg >= 70) {
        s->grade = 'C';
    } else if (s->avg >= 60) {
        s->grade = 'D';
    } else if (s->avg >= 50) {
        s->grade = 'E';
    } else {
        s->grade = 'F';
    }
}

int main() {
    int n, choice;
    printf("Enter number of students: ");
    scanf("%d", &n);
    //struct Student s[n];
    struct Student *s = 0;
    s = (struct Student *) malloc (n * sizeof(struct Student));
    if (s == NULL) {
        printf("No memory allocated.\n");
        return -1;
    }
    for (int i = 0; i < n; i++) {
        printf("\nEnter data for student %d:\n", i + 1);
        printf("Roll: ");
        scanf("%d", &s[i].roll);
        printf("Name: ");
        scanf("%50s", s[i].name);
        s[i].attendedClasses = 0;
        s[i].totalClasses = 0;
        s[i].attendance = 0;
        printf("Enter marks for three subjects:\n");
        for (int j = 0; j < 3; j++) {
            scanf("%d", &s[i].marks[j]);
        }
        calculateAverage(&s[i]);
        assignGrade(&s[i]);
    }
    do {
        printf("\nMENU\n1. Update Attendance (New Class)\n2. Display Students\n3. Show shortage list\n4. Show class toppers\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                updateAttendance (s, n);
                break;
            case 2:
                displayStudents (s, n);
                break;
            case 3:
                shortageList (s, n);
                break;
            case 4:
                classTopper (s, n);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
    free (s);
    return 0;
}

void updateAttendance (struct Student s[], int n) {
    int present;
    for (int i = 0; i < n; i++) {
        printf("Is %s present? (1 = YES, 0 = NO): ", s[i].name);
        scanf("%d", &present);
        s[i].totalClasses++;
        if (present == 1) {
            s[i].attendedClasses++;
        }
        s[i].attendance = (float) (s[i].attendedClasses * 100) / s[i].totalClasses;
    }
}

void displayStudents (struct Student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Roll: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);
        printf("Attendance: %.2f%%\n", s[i].attendance);
        printf("Average Marks: %.2f\n", s[i].avg);
        printf("Grade: %c\n", s[i].grade);
    }
}

void shortageList (struct Student s[], int n) {
    printf("\nBelow 75%% attendance\n");
    for (int i = 0; i < n; i++) {
        if (s[i].attendance < 75) {
            printf("\nRoll: %d, Name: %s, Attendance: %.2f%%\n", s[i].roll, s[i].name, s[i].attendance);
        }
    }
}

void classTopper (struct Student s[], int n) {
    float max = 0;
    for (int i = 0; i < n; i++) {
        if (s[i].avg > max) {
            max = s[i].avg;
        }
    }
    printf("Class Topper\n");
    for (int i = 0; i < n; i++) {
        if (s[i].avg == max) {
            printf("Roll: %d, Name: %s, Avg: %.2f\n", s[i].roll, s[i].name, s[i].avg);
        }
    }
}
