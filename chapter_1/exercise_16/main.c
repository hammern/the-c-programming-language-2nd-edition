#include <stdio.h>

#define MAXLINE 1000
#define ARBITRARILY_LONG_INPUT_LENGTH 40

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

int main(void) {
    int len, i;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
        if (len > ARBITRARILY_LONG_INPUT_LENGTH) {
            printf("%d -> ", len);
            for (i = 0; i < ARBITRARILY_LONG_INPUT_LENGTH; ++i)
                putchar(line[i]);
            printf("...\n");
        }

    return 0;
}
