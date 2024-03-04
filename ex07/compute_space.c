#include <stdio.h>

int ft_memory_sum(int number, char c){
    if (c == 'c')
        return(number);
    else if (c == 'i')
        return(sizeof(int) * number);
    else if (c == 'd')
        return(sizeof(double) * number);
    else
        return 1;
}

int main(void){
    int i;
    int amount;
    int number;
    char unit;
    int total;

    i = 0;
    total = 0;
    scanf("%d", &amount);
    while (i < amount){
        scanf("%d %c", &number, &unit);
        if (unit == 'c' || unit == 'i' || unit == 'd')
            total = total + ft_memory_sum(number, unit);
        else {
            printf("Invalid tracking code type ");
            return 1;
        }
        i++;
    }
    printf("%d bytes", total);
    return 0;
}