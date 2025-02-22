#include <stdio.h>

#define swap(t, x, y)                                                          \
    {                                                                          \
        t temp;                                                                \
        temp = x;                                                              \
        x = y;                                                                 \
        y = temp;                                                              \
    };

int main(void) {
    int x = 1;
    int y = 2;

    printf("x: %d, y: %d\n", x, y);
    swap(int, x, y);
    printf("x: %d, y: %d\n", x, y);

    return 0;
}
