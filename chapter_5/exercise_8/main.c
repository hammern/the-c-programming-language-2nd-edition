#include <stdio.h>

#define MAXMONTH 12
#define MAXDAY 355

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int main(void) {
    int month, day;

    printf("%d\n", day_of_year(1988, 2, 29));
    printf("%d\n", day_of_year(2025, 13, 1));

    month_day(1988, 60, &month, &day);
    printf("month: %d, day: %d\n", month, day);

    month_day(2025, 366, &month, &day);
    printf("month: %d, day: %d\n", month, day);

    return 0;
}

int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (month < 1 || month > MAXMONTH || day < 1 || day > daytab[leap][month])
        return -1;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (yearday < 1 || yearday > MAXDAY + (leap ? 1 : 0)) {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
