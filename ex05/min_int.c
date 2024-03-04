#include <stdio.h>

int ft_min(int number1, int number2);

int ft_min(int number1, int number2){
    if (number1 <= number2)
        return (number1);
    else
        return (number2);
}

int main(void){
    int i, min;
    int amount;
    int number1;
    int number2;

    scanf("%d", &amount);
    if (amount > 1){
        i = 2;
        scanf("%d %d", &number1, &number2);
        min = ft_min(number1, number2);
        while (i < amount){
            scanf("%d", &number2);
            min = ft_min(min, number2);
            i++;
        }
        printf("%d", min);
    }
    else if (amount == 1){
        scanf("%d", &min);
        printf("%d", min);
    }
    else
        printf("Something wrong");
}