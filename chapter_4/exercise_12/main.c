#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

void itoa(int n, char s[]) {
    static int i;

    if (n / 10)
        itoa(n / 10, s);
    else {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }

    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}

int main(void) {
    char s[MAXLEN] = "";

    itoa(123, s);
    printf("%s\n", s);

    itoa(-123, s);
    printf("%s\n", s);

    return 0;
}
