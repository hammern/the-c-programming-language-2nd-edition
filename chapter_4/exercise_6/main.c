#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define COMMAND 'c'
#define MAXVAL 100
#define BUFFSIZE 100
#define MAXVAR 26

int getop(char[]);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);
void command(char[]);

double vars[MAXVAR];
double recent_var;

int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case COMMAND:
            command(s);
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
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor.\n");
            break;
        case '^':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case '\n':
            recent_var = pop();
            printf("result: %.8g\n", recent_var);
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

int bufp = 0;
char buf[BUFFSIZE];

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (isalpha(c) || c == '=') {
        if (c == '=') {
            i = 1;
            while ((s[1] = c = getch()) == ' ' || c == '\t')
                ;
        }
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return COMMAND;
    }

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-') {
        c = getch();
        ungetch(c);
        if (!isdigit(c) && c != '.')
            return '-';
        c = '-';
    }

    i = 0;
    if (c == '-' || isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

void print_top() {
    if (!sp)
        return;

    recent_var = pop();
    printf("top: %.8g\n", recent_var);
    push(recent_var);
}

void duplicate_top() {
    double op = pop();
    push(op);
    push(op);
};

void swap_top() {
    double op1 = pop();
    double op2 = pop();
    push(op1);
    push(op2);
};

void clear_stack() {
    for (; sp > 0; sp--)
        val[sp] = 0;
};

void command(char s[]) {
    if (strcmp(s, "print") == 0) {
        print_top();
    } else if (strcmp(s, "duplicate") == 0) {
        duplicate_top();
    } else if (strcmp(s, "swap") == 0) {
        swap_top();
    } else if (strcmp(s, "clear") == 0) {
        clear_stack();
    } else if (strcmp(s, "sin") == 0) {
        push(sin(pop()));
    } else if (strcmp(s, "exp") == 0) {
        push(exp(pop()));
    } else if (strcmp(s, "rv") == 0) {
        push(recent_var);
    } else if (strlen(s) == 2 && s[0] == '=' && s[1] >= 'a' && s[1] <= 'z') {
        vars[s[1] - 'a'] = pop();
        push(vars[s[1] - 'a']);
    } else if (strlen(s) == 1 && s[0] >= 'a' && s[0] <= 'z') {
        push(vars[s[0] - 'a']);
    } else
        printf("error: no command matched.\n");
}
