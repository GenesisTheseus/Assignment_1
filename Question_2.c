
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    int n, i, choice;
    float sum = 0;
    struct Student *ptr, *temp, *max;

    printf("Enter number of students: ");
    scanf("%d", &n);

    ptr = malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr+i)->roll_no,
              (ptr+i)->name,
              &(ptr+i)->marks);
    }

    printf("Add 2 more students? (1=Yes, 0=No): ");
    scanf("%d", &choice);

    if (choice == 1) {
        temp = realloc(ptr, (n+2) * sizeof(struct Student));

        if (temp == NULL) {
            free(ptr);
            return 1;
        }

        ptr = temp;

        for (i = n; i < n+2; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr+i)->roll_no,
                  (ptr+i)->name,
                  &(ptr+i)->marks);
        }

        n = n + 2;
    }

    max = ptr;

    for (i = 0; i < n; i++) {
        sum += (ptr+i)->marks;

        if ((ptr+i)->marks > max->marks)
            max = ptr+i;
    }

    printf("Average marks = %.2f\n", sum/n);
    printf("Highest marks student:\n");
    printf("Roll No: %d\n", max->roll_no);
    printf("Name: %s\n", max->name);
    printf("Marks: %.2f\n", max->marks);

    free(ptr);

    return 0;
}

