#include <stdio.h>

/*
 * Only having one test in the inside the loop results in a faster comparison
 * as one comparison is eliminated per iteration, while it requires only
 * one more iteration on average.
 */
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid;
    }

    if (v[low] == x)
        return low;

    return -1;
}

int main(void) {
    int v[] = {1, 2, 3, 4, 5};
    printf("%d\n", binsearch(3, v, 4));

    return 0;
}
