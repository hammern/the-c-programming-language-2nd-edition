#include <ctype.h>
#include <stdio.h>

int htoi(const char s[]) {
    int i, n, c;

    if (s[0] == '0' && tolower(s[1]) == 'x')
        i = 2;
    else
        i = 0;

    n = 0;
    for (; s[i] != '\0'; ++i) {
        c = s[i];

        if (isdigit(c))
            c = c - '0';
        else if (c >= 'a' && c <= 'f')
            c = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            c = c - 'A' + 10;
        else
            return -1;

        n = (n << 4) | (int)c;
    }

    return n;
}

int main(void) {
    printf("1 -> %d\n", htoi("1"));
    printf("a -> %d\n", htoi("a"));
    printf("A -> %d\n", htoi("A"));
    printf("FF -> %d\n", htoi("FF"));
    printf("0x1 -> %d\n", htoi("0x1"));
    printf("0XF -> %d\n", htoi("0XF"));
    printf("0xG -> %d\n", htoi("0xG"));

    return 0;
}
