#include <stdio.h>

void is_balanced(char type[], int balanced) {
    printf("%s are ", type);
    if (balanced)
        printf("balanced\n");
    else
        printf("unbalanced\n");
}

int main(void) {
    int c, prev, inside_comment, inside_single_quotes, inside_double_quotes,
        is_escape_sequence, parentheses_counter, brackets_counter,
        braces_counter;

    inside_comment = inside_single_quotes = inside_double_quotes =
        is_escape_sequence = parentheses_counter = brackets_counter =
            braces_counter = 0;
    while ((c = getchar()) != EOF) {
        if (!inside_comment && !inside_single_quotes && !inside_double_quotes) {
            if (c == '(')
                ++parentheses_counter;
            else if (c == ')')
                --parentheses_counter;
            else if (c == '[')
                ++brackets_counter;
            else if (c == ']')
                --brackets_counter;
            else if (c == '{')
                ++braces_counter;
            else if (c == '}')
                --braces_counter;
        }

        if (!inside_comment) {
            if (c == '\'' && !inside_single_quotes && !inside_double_quotes)
                inside_single_quotes = 1;
            else if (inside_single_quotes && c == '\'' &&
                     (prev != '\\' || is_escape_sequence))
                inside_single_quotes = 0;

            if (c == '\"' && !inside_single_quotes && !inside_double_quotes)
                inside_double_quotes = 1;
            else if (inside_double_quotes && c == '\"' &&
                     (prev != '\\' || is_escape_sequence))
                inside_double_quotes = 0;
        }

        if (!inside_single_quotes && !inside_double_quotes) {
            if (prev == '/' && c == '*')
                inside_comment = 1;
            else if (prev == '*' && c == '/')
                inside_comment = 0;
        }

        if (prev == '\\' && c == '\\')
            is_escape_sequence = 1;
        else
            is_escape_sequence = 0;

        prev = c;
    }

    is_balanced("parentheses", parentheses_counter == 0);
    is_balanced("brackets", brackets_counter == 0);
    is_balanced("braces", braces_counter == 0);
    is_balanced("single quotes", inside_single_quotes == 0);
    is_balanced("double quotes", inside_double_quotes == 0);
    is_balanced("comments", inside_comment == 0);

    return 0;
}
