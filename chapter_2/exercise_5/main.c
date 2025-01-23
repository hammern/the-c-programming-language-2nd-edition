#include <stdio.h>

signed int any(char s1[], char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; i++)
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;

    return -1;
}

int main(void) {
    char s1[] = "the quick brown fox jumped over the lazy dog";
    char s2[] = "hjkl";

    printf("%d\n", any(s1, s2));

    return 0;
}
