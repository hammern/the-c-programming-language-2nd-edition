#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int c;
    int (*fn)(int);

    if (strcmp(argv[0], "lower") == 0)
        fn = tolower;
    else if (strcmp(argv[0], "upper") == 0)
        fn = toupper;
    else {
        printf("error: incorrect name\n");
        return 1;
    }

    while ((c = getchar()) != EOF)
        putchar(fn(c));

    return 0;
}
