/*
Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open,
and close instead of their standard library equivalents. Perform experiments to
determine the relative speeds of the two versions.

matxo
*/

#include <fcntl.h>
#include <unistd.h>

// filecopy: copy file ifp to file ofp
void filecopy(int ifp, int ofp)
{
    ssize_t c;
    const int count = 1024;
    static char buf[1024];

    while ((c = read(ifp, buf, count)) > 0)
        write(ofp, buf, c);
}

// cat: concatenate files, version using system calls is 5 times faster
int main(int argc, char *argv[])
{
    int fp;
    char *error_str = "cat: can't open file\n";
    int error_str_len = 23;

    if (argc == 1 ) // no args; copy standard input
        filecopy(0, 1);
    else {
        while (--argc > 0) {
            if ((fp = open(*++argv, O_RDONLY)) == -1) {
                write(2, error_str, error_str_len);
                return 1;
            } else {
                filecopy(fp, 1);
                close(fp);
            }
        }
    }
    return 0;
}