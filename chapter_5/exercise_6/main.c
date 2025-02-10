#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
#define NUMBER '0'
#define BUFFSIZE 100

int p_getline(char *, int);
int p_atoi(char *);
int p_atoi_v2(char *);
void p_itoa(int, char *);
void p_reverse(char *);
int p_strindex(char *, char *);
int p_getop(char *);

int main(void) {
    char s[MAXLEN];

    printf("p_getline: %d %s\n", p_getline(s, MAXLEN), s);

    printf("p_atoi: %d\n", p_atoi("123"));

    printf("p_atoi_v2: %d\n", p_atoi_v2("-123"));

    p_itoa(-123, s);
    printf("p_itoa: %s\n", s);

    printf("p_strindex: %d\n", p_strindex(s, "2"));

    printf("p_getop: %d\n", p_getop(s));

    return 0;
}

int p_getline(char *s, int lim) {
    int c;
    char *t = s;

    for (; lim-- > 0 && (c = getchar()) != EOF && c != '\n'; s++)
        *s = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - t;
}

int p_atoi(char *s) {
    int n;

    for (n = 0; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');
    return n;
}

int p_atoi_v2(char *s) {
    int n, sign;

    for (; isspace(*s); s++)
        ;
    sign = *s == '-' ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

void p_itoa(int n, char *s) {
    int sign;
    char *t = s;

    if ((sign = n) < 0)
        n = -n;
    do {
        *t++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        *t++ = '-';
    *t = '\0';
    p_reverse(s);
}

void p_reverse(char *s) {
    int c;
    char *t;

    for (t = s + (strlen(s) - 1); s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

int p_strindex(char *s, char *t) {
    char *original_s = s;
    char *temp_s, *temp_t;

    for (; *s != '\0'; s++) {
        for (temp_s = s, temp_t = t; *temp_t != '\0' && *temp_s == *temp_t;
             temp_s++, temp_t++)
            ;
        if (temp_t > t && *temp_t == '\0')
            return s - original_s;
    }

    return -1;
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

int p_getop(char *s) {
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s + 1) = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    if (isdigit(c))
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.')
        while (isdigit(*++s = c = getch()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
