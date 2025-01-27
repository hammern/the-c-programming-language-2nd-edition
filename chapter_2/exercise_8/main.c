#include <stdio.h>

unsigned rightrot(unsigned x, int n) {
    int lowbit;

    for (; n > 0; n--) {
        lowbit = x & 1;
        x = (x >> 1) & (~0 >> 1);

        if (lowbit)
            x = x | ~(~0 >> 1);
    }

    return x;
}

int main(void) {
    printf("%b\n", rightrot(10, 2));

    return 0;
}
