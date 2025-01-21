#include <stdio.h>

float convert_to_celsius(int fahr);

int main(void) {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    printf("------------------------\nFahrenheit-Celsius "
           "Table\n------------------------\n");

    while (fahr <= upper) {
        celsius = convert_to_celsius(fahr);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}

float convert_to_celsius(int fahr) { return (5.0 / 9.0) * (fahr - 32); }
