#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000
#define DECIMAL_BASE 10
#define HEX_BASE 16

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b) {
    int i, sign;

    sign = n;
    i = 0;
    do {
        s[i] = abs(n % b);
        s[i] += s[i] < 10 ? '0' : 'A' - 10;
        i++;
    } while (n /= b);

    if (b == HEX_BASE) {
        s[i++] = 'x';
        s[i++] = '0';
    }

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main(void) {
    char s[MAXLEN] = "";

    itob(15, s, DECIMAL_BASE);
    printf("%s\n", s);

    itob(64, s, HEX_BASE);
    printf("%s\n", s);

    itob(0xFF, s, DECIMAL_BASE);
    printf("%s\n", s);

    itob(255, s, HEX_BASE);
    printf("%s\n", s);

    return 0;
}
