#include <stdio.h>

int main(void)
{
    int min;
    int max;
    int temp;
    
    scanf("%d%d", &min, &max);
    while (1)
    {
        scanf("%d", &temp);
        if (temp == -999)
            break;
        else if (temp >= min && temp <= max)
            printf("Nothing to report\n");
        else
        {
            printf("Alert!");
            break;
        }
    }
    return 0;
}