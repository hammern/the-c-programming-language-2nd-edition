#include <stdio.h>

void p_strcat(char *, char *);

int main(void) {
    char s[] = "this is a";
    char t[] = " test";

    p_strcat(s, t);
    printf("%s\n", s);

    return 0;
}

void p_strcat(char *s, char *t) {
    while (*s++ != '\0')
        ;
    s--;
    while ((*s++ = *t++) != '\0')
        ;
}
