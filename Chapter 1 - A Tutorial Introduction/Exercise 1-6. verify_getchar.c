/*
Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.

matxo
*/

#include <stdio.h>

int main()
{
    printf("To get '1' input some characters and press [enter]\n");
    printf("To get '0' press [ctrl + d]\n");
    printf("To end program press [ctrl + c]\n");
    for (;;) {
        printf("(getchar() != EOF) == %d\n", getchar() != EOF);
    }
    return 0;
}
