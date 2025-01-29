#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[], int minimum_field_width) {
    int i, j, sign;

    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if (sign < 0)
        s[i++] = '-';

    for (j = minimum_field_width - i; j > 0; j--, i++)
        s[i] = ' ';

    s[i] = '\0';

    reverse(s);
}

int main(void) {
    char s[MAXLEN] = "";

    itoa(15, s, 5);
    printf("%s\n", s);

    return 0;
}
