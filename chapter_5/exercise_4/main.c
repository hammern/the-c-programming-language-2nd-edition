#include <stdio.h>

int strend(char *, char *);

int main(void) {
    char s[] = "this is a test";
    char t1[] = "test";
    char t2[] = "wrong";

    printf("%d\n", strend(s, t1));
    printf("%d\n", strend(s, t2));

    return 0;
}

int strend(char *s, char *t) {
    int t_len = 0;

    while (*s++ != '\0')
        ;
    s--;

    while (*t++ != '\0')
        t_len++;
    t--;

    while (t_len && *s-- == *t--)
        t_len--;

    return t_len ? 0 : 1;
}
