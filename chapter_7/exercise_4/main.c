#include <stdarg.h>
#include <stdio.h>

void minscanf(char *, ...);

int main(void) {
    int day, year;
    char monthname[20];

    minscanf("%d %s %d", &day, monthname, &year);

    printf("%d %s %d\n", day, monthname, year);

    return 0;
}

void minscanf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int *ival;
    double *dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%')
            continue;
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int *);
            scanf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double *);
            scanf("%lf", dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            scanf("%s", sval);
            break;
        }
    }
    va_end(ap);
}
