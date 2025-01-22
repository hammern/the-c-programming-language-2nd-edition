#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim) {
    int c, i;

    i = 0;
    while (i < lim - 1) {
        if ((c = getchar()) != EOF) {
            if (c != '\n') {
                s[i] = c;
                ++i;
            } else
                break;
        } else
            break;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

int main(void) {
    int len;
    char line[MAXLINE];

    len = get_line(line, MAXLINE);

    return 0;
}
