#include <stdio.h>

#define MAXLEN 1000

void escape(char s[], char t[]) {
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            break;
        default:
            s[j] = t[i];
            break;
        }

        j++;
    }

    s[j] = '\0';
}

void unescape(char s[], char t[]) {
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\\':
            switch (t[++i]) {
            case 'n':
                s[j] = '\n';
                break;
            case 't':
                s[j] = '\t';
                break;
            }
            break;
        default:
            s[j] = t[i];
            break;
        }

        j++;
    }

    s[j] = '\0';
}

int main(void) {
    char s[MAXLEN] = "";
    char t[MAXLEN] = "this\tis\na test";

    printf("%s\n", t);

    escape(s, t);
    printf("%s\n", s);

    unescape(t, s);
    printf("%s\n", t);

    return 0;
}
