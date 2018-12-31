/*
Exercise 8-4. The standard library function int fseek(FILE *fp, long offset,
int origin) is identical to lseek except that fp is a file pointer instead of a
file descriptor and return value is an int status, not a position. Write fseek.
Make sure that your fseek coordinates properly with the buffering done for the
other functions of the library.

matxo
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void* malloc (size_t size);
void free(void *ptr);
int printf ( const char * format, ... );

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 // max #files open at once

#define O_WRONLY 01
#define O_RDONLY 00

#define FSTART   SEEK_SET
#define FCURRENT SEEK_CUR
#define FEND     SEEK_END

struct fflag {
    unsigned int _READ : 1;  // file open for reading
    unsigned int _WRITE : 1; // file open for writing
    unsigned int _UNBUF : 1; // file is unbuffered
    unsigned int _EOF : 1;   // EOF has occurred on this file
    unsigned int _ERR : 1;   // error occurred on this file
};

typedef struct _iobuf {
    int cnt;    // characters left
    char *ptr;  // next character position
    char *base; // location of buffer
    struct fflag flag;   // mode of file access, implemented with bit-fields
    int fd;     // file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

FILE *fopen(char *name, char *mode);
void fclose (FILE *);
void fflush(FILE* file);
int fseek(FILE *fp, long offset, int origin);

#define feof(p)   (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt > 0 ? *((p->ptr)++) = (x) : _flushbuf((x),p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666 // RW for owner, group, others

int fseek(FILE *fp, long offset, int origin)
{
    fflush(fp);
    return lseek(fp->fd, offset, origin);
}

void fclose(FILE* file)
{
    fflush(file);
    close(file->fd);
    if (file->base != NULL)
        free(file->base);
    file->cnt = file->fd = 0;
    file->flag._EOF = file->flag._ERR = file->flag._READ = file->flag._UNBUF =
        file->flag._WRITE = 0;
    file->ptr = file->base = NULL;
}

void fflush(FILE* file)
{
    if (file == NULL) {
        for (file = _iob; file < _iob + OPEN_MAX; file++) {
            if ((file->flag._WRITE) && file->cnt > 0) {
                file->ptr = file->base;
                int bufsize = (file->flag._UNBUF) ? 1 : BUFSIZ;
                write(file->fd, file->ptr, bufsize - file->cnt);
                file->cnt = bufsize;
                file->flag._EOF = file->flag._ERR = 0;
            } else if ((file->flag._READ) && file->cnt > 0) {
                file->ptr = file->base;
                file->cnt = 0;
                file->flag._EOF = file->flag._ERR = 0;
            }
        }
    } else {
        if ((file->flag._WRITE) && file->cnt > 0) {
            file->ptr = file->base;
            int bufsize = (file->flag._UNBUF) ? 1 : BUFSIZ;
            write(file->fd, file->ptr, bufsize - file->cnt);
            file->cnt = bufsize;
            file->flag._EOF = file->flag._ERR = 0;
        } else if ((file->flag._READ) && file->cnt > 0) {
            file->ptr = file->base;
            file->cnt = 0;
            file->flag._EOF = file->flag._ERR = 0;
        }
    }
}

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag._READ ==0 || fp->flag._WRITE == 0)
            break; // found free slot
    if (fp >= _iob + OPEN_MAX) // no free slots
        return NULL;
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1) // couldn't access name
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    return fp;
}


// _fillbuf: allocate and fill input buffer
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!fp->flag._READ || fp->flag._EOF || fp->flag._ERR)
        return EOF;
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) // no buffer yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF; // can't get buffer
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

// _flushbuf: allocate and flush output buffer
int _flushbuf(int n, FILE * fp)
{
    int bufsize;

    if (!fp->flag._WRITE || fp->flag._EOF || fp->flag._ERR)
        return EOF;
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {// no buffer yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;   // can't get buffer
        else {
            fp->cnt = bufsize - 1;
            fp->ptr = fp->base;
        }
    }
    if (bufsize == 1)
        return write(fp->fd, &n, 1);
    else {
        *((fp->ptr)++) = n;
        
        fp->ptr = fp->base;
        write(fp->fd, fp->ptr, bufsize - fp->cnt);
        fp->cnt = bufsize;
        return fp->cnt;
    }
}

FILE _iob[OPEN_MAX] = { // stdin, stdout, stderr
    { 0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0 }, // _READ
    { 0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1 }, // _WRITE
    { 0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2 }  // _WRITE && _UNBUF
};

// filecopy: copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

// cat: concatenate files start after first 100 characters (to test fseek)
int main(int argc, char *argv[])
{
    char file_error[] = "error: can't open file";
    int file_error_len = 22;
    FILE *fp;

    if (argc == 1 ) { // no args; copy standard input
        filecopy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                write(2, file_error, file_error_len);
                return 1;
            } else {
                int d = fseek(fp, 100, FSTART);
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}