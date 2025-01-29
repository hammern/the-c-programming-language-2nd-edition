#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

/*
 * The largest negative number is equal to -(INT_MAX + 1).
 * Therefore, negating n in itoa (n = -n) doesn't work as (INT_MAX + 1) is too
 * large to be stored in a regular int. We can circumvent this by using the
 * absolute value of n % 10 when calculating each char.
 */

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main(void) {
    char s[MAXLEN] = "";

    itoa(INT_MIN, s);
    printf("%s\n", s);

    return 0;
}
