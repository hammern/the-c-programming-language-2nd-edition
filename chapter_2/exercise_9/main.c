#include <stdio.h>

/*
 * x &= (x - 1) deletes the rightmost 1-bit in x
 *
 * When subtracting x by 1 we change x from an even number to an odd number or
 * vice versa. This causes the rightmost bit to reverse and when combined with
 * the & operator, zeroes it, as 0 & 1 = 0.
 *
 * For example:
 * x = 3
 * 3 & (3 - 1)
 * 0011 & (0010) = 0010
 */

int bitcount(unsigned x) {
    int b;

    for (b = 0; x != 0; x &= (x - 1))
        b++;

    return b;
}

int main(void) {
    printf("%d\n", bitcount(3));

    return 0;
}
