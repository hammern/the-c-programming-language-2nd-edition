#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, int y) {
    int a = x & ~(~(~0 << n) << (p + 1 - n));
    int b = (y & ~(~0 << n)) << (p + 1 - n);

    return a | b;
}

int main(void) {
    printf("%b\n", setbits(10, 4, 3, 5));

    return 0;
}
