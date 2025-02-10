#include <stdio.h>

static char *daytab[2] = {
    (char[]){0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    (char[]){0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int main(void) {
    int month, day;

    printf("%d\n", day_of_year(1988, 2, 29));

    month_day(1988, 60, &month, &day);
    printf("month: %d, day: %d\n", month, day);

    return 0;
}

int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
