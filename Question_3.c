
#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial add(polynomial a, polynomial b) {
    polynomial c;
    int i, exp;

    c.degree = (a.degree > b.degree) ? a.degree : b.degree;

    for (i = 0; i <= c.degree; i++) {
        exp = c.degree - i;
        c.coef[i] = 0.0f;

        if (exp <= a.degree)
            c.coef[i] += a.coef[a.degree - exp];

        if (exp <= b.degree)
            c.coef[i] += b.coef[b.degree - exp];
    }

    return c;
}

void display(polynomial p) {
    int i, exp, first = 1;
    float value;

    for (i = 0; i <= p.degree; i++) {
        value = p.coef[i];
        exp = p.degree - i;

        if (value > -0.000001f && value < 0.000001f)
            continue;

        if (!first) {
            printf(value > 0 ? " + " : " - ");
        } else if (value < 0) {
            printf("-");
        }

        if (value < 0)
            value = -value;

        if (exp == 0) {
            printf("%g", value);
        } else if (exp == 1) {
            if (value == 1.0f)
                printf("x");
            else
                printf("%gx", value);
        } else {
            if (value == 1.0f)
                printf("x^%d", exp);
            else
                printf("%gx^%d", value, exp);
        }

        first = 0;
    }

    if (first)
        printf("0");
    printf("\n");
}

int readPolynomial(polynomial *p) {
    int i;

    printf("Enter degree (0 to 100): ");
    if (scanf("%d", &p->degree) != 1 ||
        p->degree < 0 || p->degree > 100) {
        printf("Invalid degree.\n");
        return 0;
    }

    printf("Enter coefficients from highest degree to constant term:\n");
    for (i = 0; i <= p->degree; i++) {
        if (scanf("%f", &p->coef[i]) != 1) {
            printf("Invalid coefficient.\n");
            return 0;
        }
    }
    return 1;
}

int main(void) {
    polynomial a, b, c;

    printf("First polynomial:\n");
    if (!readPolynomial(&a))
        return 1;

    printf("Second polynomial:\n");
    if (!readPolynomial(&b))
        return 1;

    c = add(a, b);

    printf("\nPolynomial A: ");
    display(a);
    printf("Polynomial B: ");
    display(b);
    printf("Sum: ");
    display(c);

    return 0;
}
