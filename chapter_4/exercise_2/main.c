#include <ctype.h>
#include <math.h>
#include <stdio.h>

double atof(char s[]) {
    double val, power;
    int i, sign, e_sign, e_power;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    if (tolower(s[i++]) == 'e') {
        e_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '-' || s[i] == '+')
            i++;

        for (; isdigit(s[i]); i++)
            e_power = 10 * e_power + (s[i] - '0');

        return val * pow(10, e_sign * e_power);
    }

    return val;
}

int main(void) {
    printf("%f\n", atof("10"));
    printf("%.20f\n", atof("1.0e10"));
    printf("%.20f\n", atof("123.45e-6"));

    return 0;
}
