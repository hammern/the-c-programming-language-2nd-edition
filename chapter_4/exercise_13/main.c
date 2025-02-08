#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

void reverse(char s[]) {
    static int i;
    int j, c;

    j = strlen(s) - i - 1;
    if (i < j) {
        c = s[i];
        s[i++] = s[j];
        s[j] = c;
        reverse(s);
    } else {
        i = 0;
    }
}

int main(void) {
    char s[MAXLEN] = "the quick brown fox jumped over the lazy dog";

    reverse(s);
    printf("%s\n", s);

    return 0;
}
