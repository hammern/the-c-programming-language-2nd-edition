#include <stdio.h>

unsigned invert(unsigned x, int p, int n) {
    return x ^ (~(~0 << n) << (p + 1 - n));
}

int main(void) {
    printf("%b\n", invert(10, 2, 3));

    return 0;
}
