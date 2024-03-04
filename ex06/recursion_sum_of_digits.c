#include <stdio.h>

int ft_recursion_sum(int number){
    if(number >= 10){
        return ((number % 10)+ ft_recursion_sum(number / 10));
    }
    else
        return (number % 10);
}

int main(void){
    int number;
    int result;

    scanf("%d", &number);
    result = ft_recursion_sum(number);
    printf("%d", result);
}