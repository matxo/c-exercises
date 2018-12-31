/*
Exercise 7-9. Functions like isupper can be implemented to save space or to save
time. Explore both possibilities.

matxo
*/

#include <stdio.h>
#include <string.h>

// isupper(c) non-zero if c is upper case, 0 if not
// saves space
int isupper_space(int c)
{
    return (c >= 'A' && c <= 'Z');
}

// isupper(c) non-zero if c is upper case, 0 if not
// saves time
int CHARS[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#define isupper_time(c) (CHARS[(unsigned char)c])

// test two versino os isupper
int main(int argc, char *argv[]) {
    char str[] = "YODA sais: \"Test StRing This iS, yess...\"\n";
    int l = strlen(str);
    printf("%s", str);

    
    for (int i = 0; i < l; i++) {
        printf("%d", isupper_space(str[i]));
    }
    printf("\tisupper_space\n");
    
    for (int i = 0; i < l; i++) {
        printf("%d", isupper_time(str[i]));
    }
    printf("\tisupper_time\n");
}


