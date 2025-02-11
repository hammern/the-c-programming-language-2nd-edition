#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define BUFFSIZE 10000

char *lineptr[MAXLINES];
static int numeric = 0;
static int reverse = 0;
static int fold = 0;
static int directory = 0;

int readlines(char *[], int, char[]);
void writelines(char *[], int);

void quicksort(void *[], int, int, int (*)(void *, void *));
int (*getcmpfn(void))(void *, void *);

int main(int argc, char *argv[]) {
    int nlines, c;
    char buf[BUFFSIZE];

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'f':
                fold = 1;
                break;
            case 'd':
                directory = 1;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                break;
            }
        }
    }

    if (argc) {
        printf("Usage: sort -n -r -f -d\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES, buf)) >= 0) {
        quicksort((void **)lineptr, 0, nlines - 1, getcmpfn());
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
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

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i)
        if (reverse ? ((*comp)(v[i], v[left]) > 0)
                    : ((*comp)(v[i], v[left]) < 0))
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1, comp);
    quicksort(v, last + 1, right, comp);
}

int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int dircmp(char *s1, char *s2) {
    char c1, c2;

    do {
        if (directory) {
            while (*s1 != '\0' && !isalnum(*s1) && !isblank(*s1))
                s1++;
            while (*s2 != '\0' && !isalnum(*s2) && !isblank(*s1))
                s2++;
        }

        c1 = fold ? tolower(*s1) : *s1;
        s1++;
        c2 = fold ? tolower(*s2) : *s2;
        s2++;

        if (c1 == c2 && c1 == '\0')
            return 0;
    } while (c1 == c2);

    return c1 - c2;
}

int (*getcmpfn(void))(void *, void *) {
    if (numeric)
        return (int (*)(void *, void *))numcmp;
    else if (directory)
        return (int (*)(void *, void *))dircmp;
    else if (fold)
        return (int (*)(void *, void *))strcasecmp;
    else
        return (int (*)(void *, void *))strcmp;
}
