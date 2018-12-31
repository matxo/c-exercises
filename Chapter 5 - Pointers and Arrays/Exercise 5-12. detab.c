/*
Exercise 5-12. Extend entab and detab to accept the shorthand entab -m +n to
mean tab stops every n columns, starting at column m. Choose convenient (for the
user) default behavior.

matxo
*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LINE 1000
#define MAX_TAB_STOPS 100
#define DEFAULT_TAB 8

int get_line(char s[], int lim);
int get_tab_stops(int argc, char *argv[], int max_tab_stops, int tab_stops[]);
void detab(char *str, int max_tab_stops, int tab_stops[]);

int len, tab_stops[MAX_TAB_STOPS];
char line[BUFFER_LINE];

int main(int argc, char *argv[])
{
    if (get_tab_stops(argc, argv, MAX_TAB_STOPS, tab_stops) == -1)
        return -1;
    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        detab(line, MAX_TAB_STOPS, tab_stops);
    }
}

// detab: replaces strings of tabs by the spaces to achieve the same spacing, 
//      accepts tab_stops as argument
void detab(char *str, int max_tab_stops, int tab_stops[])
{
    int spaces = 0;
    int columns = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            spaces++;
            columns++;
        } else if (str[i] == '\t') {
            int next_tab_stop = 0;
            for (int t = 0; t < max_tab_stops; t++)
                if (columns < tab_stops[t]) {
                    next_tab_stop = tab_stops[t];
                    break;
                }
            if (next_tab_stop) {
                spaces  += next_tab_stop - columns;
                columns = next_tab_stop;
            } else {
                spaces++;
                columns++;
            }
        } else {
            while (spaces) {
                putchar(' ');
                spaces--;
            }
            putchar(str[i]); // print other chars
            columns++;
        }
    }
}

// set_tab_stops: reads a list of tab stops as arguments, uses the default tab 
//      settings if there are no or to few arguments
//      entab -m +n tab stops every n columns, starting at column m
int get_tab_stops(int argc, char *argv[], int max_tab_stops, int tab_stops[])
{
    static char * help = "error: tab stops list should have positive numbers in"
        " increasing order (e.g. 4 8 12);\n\tentab -m +n tab stops every n "
        "columns, starting at column m\n";
    int i, j = 0;
    int repeat_column = 0;
    int starting_column = 0;
    for (i = 0; (argc >= i + 2) && j < MAX_TAB_STOPS; i++) {
        int t;
        if (argv[i+1][0] == '-' || argv[i+1][0] == '+') {
            t = atoi(argv[i+1]);
            if (t < 0)
                starting_column = t;
            else if (t > 0)
                repeat_column = t;
            else {
                printf("%s", help);
                return -1;
            }
        } else if((t = atoi(argv[i+1])) > 0 && (t > tab_stops[j-1] || i == 0)) {
            tab_stops[j++] = t;
        } else {
            printf("%s", help);
            return -1;
        }
    }
    if (argc <= 1) {
        tab_stops[j] = DEFAULT_TAB;
        j++;
    }
    if (starting_column)
        j = -(++starting_column);
    if (repeat_column == 0)
        repeat_column = DEFAULT_TAB;
    for (; j < MAX_TAB_STOPS; j++)
        tab_stops[j] = tab_stops[j - 1] + repeat_column;
    return 0;
}

// get_line: read a line into s, return length
int get_line(char s[], int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
