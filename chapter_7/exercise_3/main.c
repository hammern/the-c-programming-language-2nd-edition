#include <stdarg.h>
#include <stdio.h>

void minprintf(char *, ...);

int main(void) {
    minprintf("%d %f %s %o %x %c", 42, 4.2, "test", 9, 10, '\n');

    return 0;
}

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    char cval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'o':
            ival = va_arg(ap, int);
            printf("%o", ival);
            break;
        case 'x':
        case 'X':
            ival = va_arg(ap, int);
            printf("%x", ival);
            break;
        case 'c':
            cval = va_arg(ap, int);
            putchar(cval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}
