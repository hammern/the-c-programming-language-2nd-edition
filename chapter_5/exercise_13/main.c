#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINES 10
#define MAXLINES 5000
#define BUFFSIZE 10000

char *lineptr[MAXLINES];

int readlines(char *[], int, char[]);
void writelines(char *[], int, int);

int main(int argc, char *argv[]) {
    int nlines, maxlines;
    char buf[BUFFSIZE];

    if (argc <= 1)
        nlines = DEFAULT_LINES;
    else if (argc == 2 && *argv[1] == '-')
        nlines = atoi(argv[1] + 1);

    if (nlines < 1 || nlines > MAXLINES)
        nlines = DEFAULT_LINES;

    if ((maxlines = readlines(lineptr, MAXLINES, buf)) >= 0) {
        writelines(lineptr, nlines, maxlines);
        return 0;
    } else {
        printf("error: input too big\n");
        return 1;
    }
}

#define MAXLEN 1000
int get_line(char *, int);

int readlines(char *lineptr[], int maxlines, char buf[]) {
    int len, nlines;
    char *p, line[MAXLEN];

    p = buf;
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (BUFFSIZE + buf - p) < len)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

int get_line(char *s, int lim) {
    int c;
    char *t = s;

    for (; lim-- > 0 && (c = getchar()) != EOF && c != '\n'; s++)
        *s = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - t;
}

void writelines(char *lineptr[], int nlines, int maxlines) {
    int i;

    for (i = maxlines <= nlines ? 0 : maxlines - nlines; i < maxlines; i++)
        printf("%s\n", lineptr[i]);
}
