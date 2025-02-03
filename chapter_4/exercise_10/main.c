#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFFSIZE 100

int get_line(char[], int);
int getop(char[]);
void push(double);
double pop(void);

int main(void) {
    int i, bufp;
    double op2;
    char s[MAXOP], buf[BUFFSIZE];

    while (get_line(s, MAXOP) > 0) {
        bufp = 0;

        for (i = 0; s[i] != '\0'; i++) {
            if (s[i] == ' ' || s[i] == '\t')
                continue;

            if (isdigit(s[i]) || s[i] == '.') {
                while (isdigit(s[i]) || s[i] == '.') {
                    buf[bufp++] = s[i];
                    i++;
                }

                buf[bufp] = '\0';
                bufp = 0;
                push(atof(buf));
                continue;
            }

            switch (s[i]) {
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
                printf("error: unknown command %c.\n", s[i]);
                break;
            }
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

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}
