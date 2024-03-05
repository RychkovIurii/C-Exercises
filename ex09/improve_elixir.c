#include <stdio.h>

//Write your function prototype here
void ft_modifier(int *ageAddr);

int main(void){
	int age;
	int *ageAddr = &age;
	scanf("%d", ageAddr);
	printf("Your current age is %d.\n", age);

	//Write your function call here
    ft_modifier(ageAddr);

	printf("Your new age will be %d!\n", age);
	return 0;
}


//Write your function here
void ft_modifier(int *ageAddr){
    if (*ageAddr < 21)
        *ageAddr = *ageAddr * 2;
    else
        *ageAddr = *ageAddr - 10;
    return 0;
}