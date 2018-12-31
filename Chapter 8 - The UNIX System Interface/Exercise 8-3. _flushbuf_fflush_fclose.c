/*
Exercise 8-3. Design and write _flushbuf , fflush , and fclose.

matxo
*/

#include <fcntl.h>
#include <unistd.h>

void* malloc (size_t size);
void free(void *ptr);
int printf ( const char * format, ... );

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 // max #files open at once

typedef struct _iobuf {
    int cnt;    // characters left
    char *ptr;  // next character position
    char *base; // location of buffer
    int flag;   // mode of file access
    int fd;     // file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ =  01, // file open for reading
    _WRITE = 02, // file open for writing
    _UNBUF = 04, // file is unbuffered
    _EOF =  010, // EOF has occurred on this file
    _ERR =  020  // error occurred on this file
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

FILE *fopen(char *name, char *mode);
void fclose (FILE *);
void fflush(FILE* file);

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

void fclose(FILE* file)
{
    fflush(file);
    close(file->fd);
    if (file->base != NULL)
        free(file->base);
    file->flag = file->cnt = file->fd = 0;
    file->ptr = file->base = NULL;
}

void fflush(FILE* file)
{
    if (file == NULL) {
        for (file = _iob; file < _iob + OPEN_MAX; file++) {
            if ((file->flag & _WRITE) && file->cnt > 0) {
                file->ptr = file->base;
                int bufsize = (file->flag & _UNBUF) ? 1 : BUFSIZ;
                write(file->fd, file->ptr, bufsize - file->cnt);
                file->cnt = bufsize;
            }
        }
    } else {
        if ((file->flag & _WRITE) && file->cnt > 0) {
            file->ptr = file->base;
            int bufsize = (file->flag & _UNBUF) ? 1 : BUFSIZ;
            write(file->fd, file->ptr, bufsize - file->cnt);
            file->cnt = bufsize;
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
        if ((fp->flag & (_READ | _WRITE)) == 0)
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}


// _fillbuf: allocate and fill input buffer
int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) // no buffer yet
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF; // can't get buffer
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

// _flushbuf: allocate and flush output buffer
int _flushbuf(int n, FILE * fp)
{
    int bufsize;

    if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
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
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

// filecopy: copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

// cat: concatenate files
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
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}