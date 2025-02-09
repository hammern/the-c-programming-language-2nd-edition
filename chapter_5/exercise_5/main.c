#include <stdio.h>

void p_strncpy(char *, char *, int);
void p_strncat(char *, char *, int);
int p_strncmp(char *, char *, int);

int main(void) {
    char s[] = "this is a ";
    char t[] = "test";

    p_strncpy(s, t, 3);
    printf("%s\n", s);

    p_strncat(s, t, 2);
    printf("%s\n", s);

    printf("%d\n", p_strncmp(s, t, 2));

    return 0;
}

void p_strncpy(char *s, char *t, int n) {
    while ((*s++ = *t++) && --n)
        ;
}

void p_strncat(char *s, char *t, int n) {
    while (*s++ != '\0')
        ;
    s--;
    while ((*s++ = *t++) != '\0' && --n)
        ;
    *s = '\0';
}

int p_strncmp(char *s, char *t, int n) {
    for (; *s == *t && n > 0; s++, t++, n--)
        if (*s == '\0')
            return 0;
    return *s - *t;
}
