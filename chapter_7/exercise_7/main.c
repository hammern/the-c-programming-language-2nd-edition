#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

struct {
    unsigned int except : 1;
    unsigned int number : 1;
} flags;

void find(FILE *, char *, char *);

int main(int argc, char **argv) {
    char *prog = argv[0];
    int c;
    FILE *fp;
    char *pattern;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'x':
                flags.except = 1;
                break;
            case 'n':
                flags.number = 1;
                break;
            default:
                fprintf(stderr, "%s: illegal option %c\n", prog, c);
                return 1;
            }
        }
    }

    if (argc < 1) {
        fprintf(stderr, "Usage: %s -x -n [files...] pattern\n", prog);
        return 1;
    }

    pattern = argv[argc - 1];
    if (argc == 1) {
        fp = stdin;
        find(stdin, "", pattern);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                return 1;
            }

            find(fp, *argv++, pattern);
            fclose(fp);
        }
    }

    return 0;
}

void find(FILE *fp, char *filename, char *pattern) {
    char line[MAXLINE];
    long lineno = 0;

    while (fgets(line, MAXLINE, fp) != NULL) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != flags.except) {
            if (*filename)
                printf("%s - ", filename);
            if (flags.number)
                printf("%ld: ", lineno);
            printf("%s", line);
        }
    }
}
