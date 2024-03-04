#include <stdio.h>

int ft_memory_sum(int number, char c){
    if (c == 'c')
        return(number);
    else if (c == 'i')
        return(sizeof(int) * number);
    else if (c == 'd')
        return(sizeof(double) * number);
    else if (c == 's')
        return(sizeof(short) * number);
    else
        return 1;
}

void ft_print_bytes(int bytes){
    if (bytes / 1000000 > 0){
        printf("%d MB and %d KB and %d B", bytes / 1000000, (bytes % 1000000) / 1000, (bytes % 1000000) % 1000);
    }
    else if (bytes / 1000 > 0) {
        printf("%d KB and %d B", bytes / 1000, bytes % 1000);
    } else {
        printf("%d B", bytes);
    }
}

int main(void){
    int number;
    char unit;
    int total;

    scanf("%c %d", &unit, &number);
    total = ft_memory_sum(number, unit);
    ft_print_bytes(total);
    return 0;
}