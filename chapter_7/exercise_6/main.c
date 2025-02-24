#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void filecmp(FILE *, char *, FILE *, char *);

int main(int argc, char **argv) {
    FILE *fp1, *fp2;
    char *prog = argv[0];
    char *filename1 = argv[1];
    char *filename2 = argv[2];

    if (argc != 3) {
        fprintf(stderr, "%s: incorrect number of arguments\n", prog);
        return 1;
    }

    if ((fp1 = fopen(filename1, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[1]);
        return 1;
    }

    if ((fp2 = fopen(filename2, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", prog, argv[2]);
        return 1;
    }

    filecmp(fp1, filename1, fp2, filename2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}

void filecmp(FILE *fp1, char *filename1, FILE *fp2, char *filename2) {
    char line1[MAXLINE], line2[MAXLINE];

    while (fgets(line1, MAXLINE, fp1) != NULL &&
           fgets(line2, MAXLINE, fp2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            printf("%s: %s", filename1, line1);
            printf("%s: %s", filename2, line2);
            break;
        }
    }
}
