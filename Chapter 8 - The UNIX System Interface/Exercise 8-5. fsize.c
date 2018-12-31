/*
Exercise 8-5. Modify the fsize program to print the other information contained
in the inode entry.

matxo
*/

#include <sys/dir.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>     // flags for read and write
#include <sys/types.h> // typedefs
#include <sys/stat.h>  // structure returned by stat
#include <unistd.h>

#define MAX_PATH 1024

typedef struct {    // portable directory entry
    long ino;               // inode number
    char name[NAME_MAX+1];  // name + '\0' terminator
} Dirent;

typedef struct {
    int fd;
    Dirent d;
} MYDIR;

void* malloc (size_t size);
void free(void *ptr);
MYDIR *myopendir(char *dirname);
Dirent *myreaddir(MYDIR *dfd);
void myclosedir(MYDIR *dfd);
char *name;
struct stat stbuf;

int fstat(int fd, struct stat *);
void dirwalk(char *, void (*fcn)(char *));
void fsize(char *);

// print file name
int main(int argc, char **argv)
{
    if (argc == 1) // default: current directory
        fsize(".");
    else
    while (--argc > 0)
        fsize(*++argv);
    return 0;
}

// fsize: print the name of file "name"
void fsize(char *name)
{
    struct stat stbuf;
    
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("UID:%-8ldGID:%-8ldhard links:%-8ldmod:%-8ld size:%-8ldname:%s\n", 
        stbuf.st_uid, stbuf.st_gid, stbuf.st_nlink, stbuf.st_mode, 
        stbuf.st_size, name);
}

// dirwalk: apply fcn to all files in dir
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    MYDIR *dfd;

    if ((dfd = myopendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = myreaddir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
        continue; // skip self and parent
        if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    myclosedir(dfd);
}

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

// myopendir: open a directory for myreaddir calls
MYDIR *myopendir(char *dirname)
{
    int fd;
    struct stat stbuf;
    MYDIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1
            || fstat(fd, &stbuf) == -1
            || (stbuf.st_mode & S_IFMT) != S_IFDIR
            || (dp = (MYDIR *) malloc(sizeof(MYDIR))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
}

// myclosedir: close directory opened by myopendir
void myclosedir(MYDIR *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

// local directory structure
// myreaddir: read directory entries in sequence
Dirent *myreaddir(MYDIR *dp)
{
    struct direct dirbuf; // local directory structure
    static Dirent d;
    // return: portable structure
    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) // slot not in use
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0'; // ensure termination
        return &d;
    }
    return NULL;
}