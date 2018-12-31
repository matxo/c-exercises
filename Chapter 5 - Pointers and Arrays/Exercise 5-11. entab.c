/*
Exercise 5-11. Modify the program entab and detab (written as exercises in
Chapter 1) to accept a list of tab stops as arguments. Use the default tab
settings if there are no arguments.

matxo
*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LINE 1000
#define MAX_TAB_STOPS 100
#define DEFAULT_TAB 8

int get_line(char s[], int lim);
int get_tab_stops(int argc, char *argv[], int max_tab_stops, int tab_stops[]);
void entab(char *str, int max_tab_stops, int tab_stops[]);

int len, tab_stops[MAX_TAB_STOPS];
char line[BUFFER_LINE];

int main(int argc, char *argv[])
{
    if (get_tab_stops(argc, argv, MAX_TAB_STOPS, tab_stops) == -1)
        return -1;
    while ((len = get_line(line, BUFFER_LINE)) > 0) {
        entab(line, MAX_TAB_STOPS, tab_stops);
    }
}

// entab: replaces strings of blanks by the min. number of tabs and blanks to
//      achieve the same spacing, accepts tab_stops as argument
void entab(char *str, int max_tab_stops, int tab_stops[])
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
                int stating_column = columns - spaces;
                int next_tab_stop = 0;
                for (int t = 0; t < max_tab_stops; t++)
                    if (stating_column < tab_stops[t]) {
                        next_tab_stop = tab_stops[t];
                        break;
                    }
                int columns_to_next_tab_stop = next_tab_stop - stating_column;
                if (spaces >= columns_to_next_tab_stop) {
                    putchar('\t');
                    spaces -= columns_to_next_tab_stop;
                } else {
                    putchar(' ');
                    spaces--;
                }
            }
            putchar(str[i]); // print other chars
            columns++;
        }
    }
}

// set_tab_stops: reads a list of tab stops as arguments, uses the default tab 
//      settings if there are no or to few arguments
int get_tab_stops(int argc, char *argv[], int max_tab_stops, int tab_stops[])
{
    int i;
    for (i = 0; (argc >= i + 2) && i < MAX_TAB_STOPS; i++) {
        int t;
        if ((t = atoi(argv[i+1])) > 0 && (t > tab_stops[i-1] || i == 0)) {
            tab_stops[i] = t;
        } else {
            printf("%s\n", "error: tab stops should be positive numbers in "
                "increasing order (e.g. 4 8 12)");
            return -1;
        }
    }
    if (argc <= 1) {
        tab_stops[0] = DEFAULT_TAB;
        i++;
    }
    for (; i < MAX_TAB_STOPS; i++)
        tab_stops[i] = tab_stops[i - 1] + DEFAULT_TAB;
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
