#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1

int main(int argc, char **argv) {
    int fd;
    void filecopy(int, int);

    if (argc == 1)
        filecopy(STDIN, STDOUT);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "cat: can't open %s\n", *argv);
                exit(1);
            } else {
                filecopy(fd, STDOUT);
                close(fd);
            }

    exit(0);
}

void filecopy(int ifd, int ofd) {
    char buf[BUFSIZ];
    int n;

    while ((n = read(ifd, buf, BUFSIZ)) > 0)
        if (write(ofd, buf, n) != n) {
            fprintf(stderr, "cat: write error\n");
            exit(1);
        }
}
