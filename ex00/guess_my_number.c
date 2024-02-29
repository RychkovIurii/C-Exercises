#include <stdio.h>

int main(void)
{
    int number;
    int guess;
    int tries = 0;
    
    scanf("%d", &number);
    while (1)
    {
        scanf("%d", &guess);
        tries++;
        if (guess == number) {
            break;
        } 
        else if (guess < number) {
            printf("it is more\n");
        } 
        else {
            printf("it is less\n");
        }
    }
    printf("Number of tries needed:\n");
    printf("%d\n", tries);
    return 0;
}