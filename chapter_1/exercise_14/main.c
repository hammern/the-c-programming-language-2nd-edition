#include <stdio.h>

#define ALPHA_CHARACTERS_COUNT 26
#define NUMBER_CHARACTERS_COUNT 10

int main(void) {
    int c, i, j;
    int alpha_frequency[ALPHA_CHARACTERS_COUNT];
    int number_frequency[NUMBER_CHARACTERS_COUNT];

    for (i = 0; i < ALPHA_CHARACTERS_COUNT; ++i)
        alpha_frequency[i] = 0;

    for (i = 0; i < NUMBER_CHARACTERS_COUNT; ++i)
        number_frequency[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z')
            ++alpha_frequency[c - 'a'];
        else if (c >= '0' && c <= '9')
            ++number_frequency[c - '0'];
    }

    for (i = 0; i < ALPHA_CHARACTERS_COUNT; ++i) {
        printf("%c", 'a' + i);

        for (j = 0; j < alpha_frequency[i]; ++j)
            putchar('*');

        putchar('\n');
    }

    for (i = 0; i < NUMBER_CHARACTERS_COUNT; ++i) {
        printf("%c", '0' + i);

        for (j = 0; j < number_frequency[i]; ++j)
            putchar('*');

        putchar('\n');
    }

    return 0;
}
