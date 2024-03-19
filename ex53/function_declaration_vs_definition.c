#include <stdio.h>

double ftoc(int);
double ctof(int);


int main(void) {

    int usertemp;
    char unit;
    double convertedtemp;

    scanf("%d %c", &usertemp, &unit);
    if (unit=='C'){
        convertedtemp = ctof(usertemp);
        printf("%.1lf F", convertedtemp);
    } else if (unit=='F'){
        convertedtemp = ftoc(usertemp);
        printf("%.1lf C", convertedtemp);
    }

    return 0;

}

/* Conversion from Celsius to Fahrenheit: */
double ctof(int x){
    return((9.0/5)*x+32);
}

/* Conversion from Fahrenheit to Celsius: */
double ftoc(int x){
    return(5.0/9*(x-32));
}