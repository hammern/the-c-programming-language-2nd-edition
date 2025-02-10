#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define BUFFSIZE 10000

char *lineptr[MAXLINES];

int readlines(char *[], int, char[]);
void writelines(char *[], int);

void qsort(char *[], int, int);

int main(void) {
    int nlines;
    char buf[BUFFSIZE];

    if ((nlines = readlines(lineptr, MAXLINES, buf)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
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

void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(char *v[], int left, int right) {
    int i;
    int last;

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; ++i)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}
