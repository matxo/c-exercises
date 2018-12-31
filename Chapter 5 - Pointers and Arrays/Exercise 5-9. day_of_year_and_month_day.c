/*
Exercise  5-9. Rewrite  the  routines day_of_year and month_day with pointers
instead of indexing.

matxo
*/

#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int y, m, d;
    printf("year month day: ");
    scanf("%d %d %d", &y, &m, &d);

    int year_day;
    if ((year_day = day_of_year(y, m, d)) == -1) {
        printf("error: invalid date\n");
        return -1;
    }
    printf("y: %d\tm: %d\td: %d\n", y, m, d);
    if (month_day(y, year_day, &m, &d) == -1) {
        printf("error: invalid year or yearday\n");
        return -1;
    }
    printf("day of year: %d\tmonth: %d\tday: %d\n", year_day, m, d);
}

static char daytab[][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// day_of_year: set day of year from month & day; return -1 if error (pointer
//      version)
int day_of_year(int year, int month, int day)
{
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return -1;
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (day > *(*(daytab+leap)+month))
        return -1;
    for (i = 1; i < month; i++)
        day += *(*(daytab+leap)+i);
    return day;
}

// month_day: set month, day from day of year (pointer version)
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    if (year < 0)
        return -1;
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if ((leap && yearday > 365) || (!leap && yearday > 366))
        return -1;
    for (i = 1; yearday > *(*(daytab+leap)+i); i++)
        yearday -= *(*(daytab+leap)+i);
    *pmonth = i;
    *pday = yearday;
    return 1;
}
