#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(double);
double pop(void);

int main(int argc, char *argv[]) {
    int i;
    double op2;

    for (i = 1; i < argc; i++) {
        op2 = atof(argv[i]);

        if (op2 || strcmp(argv[i], "0") == 0) {
            push(op2);
            continue;
        }

        switch (*argv[i]) {
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor.\n");
            break;
        default:
            printf("error: unknown command %c.\n", *argv[i]);
            break;
        }
    }

    printf("result: %.8g\n", pop());

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g.\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty.\n");
        return 0.0;
    }
}
