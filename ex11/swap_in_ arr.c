#include <stdio.h>

void    ft_reverse_array(int *arr){
	int	temp;
	int	i;
    int size;

	i = 0;
    size = 6;
	while (i < size)
	{
		temp = arr[i];
		arr[i] = arr[size - 1];
		arr[size - 1] = temp;
		i = i + 1;
		size = size - 1;
	}
}    

int main(void){
    int i;
    int arr[6];
    for (i=0; i<6; i++){
        scanf("%d", &arr[i]);
    }
    ft_reverse_array(arr);
    for (i=0; i<6; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}