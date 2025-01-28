#include <ctype.h>
#include <stdio.h>

#define MAXLEN 1000

void expand(char s1[], char s2[]) {
    int i, j, k;

    for (i = j = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '-') {
            if (isalnum(s1[i - 1]) && isalnum(s1[i + 1])) {
                for (k = s1[i - 1]; k <= s1[i + 1]; k++, j++) {
                    s2[j] = k;
                }
            } else {
                s2[j++] = s1[i];
            }
        }
    }

    s2[j] = '\0';
}

int main(void) {
    char s2[MAXLEN] = "";

    expand("a-z", s2);
    printf("%s\n", s2);

    expand("a-b-c", s2);
    printf("%s\n", s2);

    expand("a-zA-Z0-9", s2);
    printf("%s\n", s2);

    expand("-a-z-", s2);
    printf("%s\n", s2);

    return 0;
}
