#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100

int getop(char[]);
void push(double);
double pop(void);

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
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
        case '\n':
            printf("result: %.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s.\n", s);
            break;
        }
    }

    return 0;
}

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

int getop(char s[]) {
    char c;
    int rc;
    double op;

    while ((rc = scanf("%c", &c)) != EOF)
        if ((s[0] = c) != ' ' && c != '\t')
            break;
    s[1] = '\0';
    if (rc == EOF)
        return EOF;
    else if (!isdigit(c) && c != '.')
        return c;
    ungetc(c, stdin);
    scanf("%lf", &op);
    sprintf(s, "%lf", op);
    return NUMBER;
}
