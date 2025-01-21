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

void trim(char line[], int last_index) {
    int i;

    for (i = 0; i <= last_index; ++i)
        putchar(line[i]);

    printf("%s", "\n\0");
}

int main(void) {
    int len, i, last_valid_char_index, newline_index;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        for (i = 0; i < len; ++i) {
            if (line[i] == '\n')
                newline_index = i;
            else if (line[i] != ' ' && line[i] != '\t')
                last_valid_char_index = i;
        }

        // blank line
        if (newline_index == 0)
            continue;

        trim(line, last_valid_char_index);
    }

    return 0;
}
