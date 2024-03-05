#include <stdio.h>

void behind(int *, int);

int main(void) {
    int array[10];
    int N, i;
    
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        scanf("%d", &array[i]);
    }
    behind(array, N);
    for (i=0; i<N; i++) {
        printf("%d\n", array[i]);
    }
    
    return 0;
}

void behind(int *arr, int players){
    int max;
    int i; 
    
    i = 0;
    max = 0;
    while (i < players){
        if (arr[i] > max)
            max = arr[i];
        i++;
    }
    i = 0;
    while (i < players){
        arr[i] = max - arr[i];
        i++;
    }
}