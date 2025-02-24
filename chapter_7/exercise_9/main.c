#include <stdio.h>

int save_space_isupper(int);
int save_time_isupper(int);

int main(void) {
    printf("%d\n", save_space_isupper('a'));
    printf("%d\n", save_space_isupper('A'));

    printf("%d\n", save_time_isupper('a'));
    printf("%d\n", save_time_isupper('A'));

    return 0;
}

int save_space_isupper(int c) { return c >= 'A' && c <= 'Z' ? 1 : 0; }

int save_time_isupper(int c) {
    static int hashtab[] = {
        ['A'] = 1, ['B'] = 1, ['C'] = 1, ['D'] = 1, ['E'] = 1, ['F'] = 1,
        ['G'] = 1, ['H'] = 1, ['I'] = 1, ['J'] = 1, ['K'] = 1, ['L'] = 1,
        ['M'] = 1, ['N'] = 1, ['O'] = 1, ['P'] = 1, ['Q'] = 1, ['R'] = 1,
        ['S'] = 1, ['T'] = 1, ['U'] = 1, ['V'] = 1, ['W'] = 1, ['X'] = 1,
        ['Y'] = 1, ['Z'] = 1};

    return hashtab[c];
}
