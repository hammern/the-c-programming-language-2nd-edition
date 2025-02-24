#include <stdio.h>

#define MAXLINE 1000

void fileprint(FILE *, char *);

int main(int argc, char **argv) {
    char *prog = argv[0];
    FILE *fp;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s [files...]\n", prog);
        return 1;
    }

    while (--argc > 0) {
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            return 1;
        }

        fileprint(fp, *argv);
        fclose(fp);
    }

    return 0;
}

void fileprint(FILE *fp, char *filename) {
    static long pagecount = 1;
    char line[MAXLINE];

    printf("\t%s\n\n", filename);
    while (fgets(line, MAXLINE, fp) != NULL)
        printf("%s", line);
    printf("\t\t\t%ld\n\f", pagecount++);
}
