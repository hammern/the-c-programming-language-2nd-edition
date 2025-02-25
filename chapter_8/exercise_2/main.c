#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPEN_MAX 20
#define PERMS 0666

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : myfillbuf(p))

typedef struct iobuf {
    int cnt;
    char *ptr;
    char *base;
    struct {
        unsigned int read : 1;
        unsigned int write : 1;
        unsigned int unbuf : 1;
        unsigned int eof : 1;
        unsigned int err : 1;
    } flags;
    int fd;
} MYFILE;
MYFILE iob[OPEN_MAX];

MYFILE *myfopen(char *, char *);
int myfillbuf(MYFILE *);

int main(int argc, char **argv) {
    MYFILE *fp;
    int c;

    if (argc == 1)
        while ((c = getchar()) != EOF)
            putchar(c);
    else
        while (--argc > 0)
            if ((fp = myfopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "cat: can't open %s\n", *argv);
                exit(1);
            } else {
                while ((c = getc(fp)) != EOF)
                    putchar(c);
            }

    exit(0);
}

MYFILE *myfopen(char *name, char *mode) {
    int fd;
    MYFILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = iob; fp < iob + OPEN_MAX; fp++)
        if (fp->flags.write == 0 && fp->flags.read == 0)
            break;
    if (fp >= iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flags.read = 1;
    else
        fp->flags.write = 1;
    return fp;
}

int myfillbuf(MYFILE *fp) {
    int bufsize;

    if (fp->flags.read == 0 || fp->flags.eof == 1 || fp->flags.err == 1)
        return EOF;
    bufsize = (fp->flags.unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, BUFSIZ);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flags.eof = 1;
        else
            fp->flags.err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}
