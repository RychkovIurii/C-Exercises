// Activity: use the math library
#include <stdio.h>
#include <math.h>

int main(void){
    int number;
    double sqrtResult;
    double e;

    scanf("%d", &number);
    sqrtResult = sqrt(number);
    printf("%.8lf\n", sqrtResult);
    e = exp(1);
    printf("%.10lf\n", e);
    printf("gcc -std=c11 -Wall -fmax-errors=10 -Wextra -lm program.c -o program\n");
    return 0;
}