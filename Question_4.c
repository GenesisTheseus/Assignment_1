#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} term;

void display(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");
    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    for (i = 1; i <= num_terms; i++)
        row_terms[a[i].col]++;

    starting_pos[0] = 0;
    for (i = 1; i < num_cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    printf("\nrow_terms[]: ");
    for (i = 0; i < num_cols; i++)
        printf("%d ", row_terms[i]);

    printf("\nstarting_pos[]: ");
    for (i = 0; i < num_cols; i++)
        printf("%d ", starting_pos[i]);
    printf("\n");

    for (i = 1; i <= num_terms; i++) {
        j = starting_pos[a[i].col]++;
        b[j + 1].row = a[i].col;
        b[j + 1].col = a[i].row;
        b[j + 1].value = a[i].value;
    }
}

int main(void) {
    term a[MAX], b[MAX];
    int rows, cols, i, j, value, count = 0;

    printf("Enter number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 ||
        rows <= 0 || cols <= 0 || rows >= MAX || cols >= MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (scanf("%d", &value) != 1) {
                printf("Invalid input.\n");
                return 1;
            }

            if (value != 0) {
                if (count >= MAX - 1) {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }
                count++;
                a[count].row = i;
                a[count].col = j;
                a[count].value = value;
            }
        }
    }

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = count;

    printf("\nOriginal matrix triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    display(b);
    printf("\nThe transposed triples are in row-major order.\n");

    return 0;
}
