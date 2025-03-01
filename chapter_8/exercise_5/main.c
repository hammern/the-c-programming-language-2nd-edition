#include <stdio.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>

void fsize(char *);

int main(int argc, char **argv) {
    if (argc == 1)
        fsize(".");
    while (--argc > 0)
        fsize(*++argv);

    return 0;
}

void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == 1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%lu %d %lu %6ld %s\n", stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink,
           stbuf.st_size, name);
}

#define MAX_PATH 256

void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
