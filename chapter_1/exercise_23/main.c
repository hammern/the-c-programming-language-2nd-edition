#include <stdio.h>

/* hello from single line comment */

/*
 * hello from multiline comment
 */

char string_test[] = "hello from /* */ inside quoted string";

int main(void) {
    int c, prev, inside_string, inside_comment;

    prev = inside_string = inside_comment = 0;
    while ((c = getchar()) != EOF) {
        if (prev != '\'' && c == '"')
            inside_string = !inside_string;
        /* hello after quote character constant */
        else if (prev == '/' && c == '*')
            inside_comment = 1;
        else if (prev == '*' && c == '/')
            inside_comment = 0;

        if (c != '/' && !inside_comment)
            putchar(c);
        else if (inside_string)
            putchar(c);

        prev = c;
    }

    return 0;
}
