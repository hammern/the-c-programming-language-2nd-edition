#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

signed int strrindex(char s[], char t[]) {
    int i, j, k;

    for (i = strlen(s); i >= 0; i--) {
        for (j = i, k = strlen(t) - 1; j >= 0 && k >= 0 && s[j] == t[k];
             j--, k--) {
            if (!k)
                return j;
        }
    }

    return -1;
}

int main(void) {
    char s[MAXLEN] = "this is a test";

    printf("%d\n", strrindex(s, "is"));
    printf("%d\n", strrindex(s, "function"));

    return 0;
}
