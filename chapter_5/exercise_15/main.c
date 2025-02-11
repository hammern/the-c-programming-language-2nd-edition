#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define BUFFSIZE 10000

char *lineptr[MAXLINES];

int readlines(char *[], int, char[]);
void writelines(char *[], int);

void quicksort(void *[], int, int, int (*)(void *, void *), int);
int numcmp(char *, char *);

int main(int argc, char *argv[]) {
    int nlines, c, numeric, reverse, fold;
    char buf[BUFFSIZE];

    numeric = reverse = fold = 0;
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
            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                break;
            }
        }
    }

    if (argc) {
        printf("Usage: sort -n -r -f\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES, buf)) >= 0) {
        quicksort((void **)lineptr, 0, nlines - 1,
                  (int (*)(void *, void *))(
                      numeric ? numcmp
                              : (int (*)(char *, char *))(fold ? strcasecmp
                                                               : strcmp)),
                  reverse);
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

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *),
               int reverse) {
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
    quicksort(v, left, last - 1, comp, reverse);
    quicksort(v, last + 1, right, comp, reverse);
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
