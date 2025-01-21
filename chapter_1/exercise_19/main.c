#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

void reverse(char line[], int length) {
    int i;

    for (i = length - 2; i >= 0; --i)
        putchar(line[i]);

    printf("%s", "\n\0");
}

int main(void) {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
        reverse(line, len);

    return 0;
}
