#include <stdio.h>
int main(void) {
    //! showMemory(start=65520)
    int array[] = {6, 2, -4, 8, 5, 1};
    int *ptr, *ptr2;
    
    printf("Array contains %d, %d, ... , %d\n", array[0], array[1], array[5]);
    printf("These are stored at %p, %p, ..., %p\n", &array[0], &array[1], &array[5]);
    // array equals &array[0]
    ptr = array;
    ptr2 = &array[0];
    
    *ptr = 10; //same as    *array = 10; if we didn't move a pointer
    *(ptr + 1) = 5;  //same as    *(array + 1) = 5;
    return 0;
}

// Terminal
// Array contains 6, 2, ... , 1
// These are stored at ffe8, ffec, ..., fffc

// main()
// int array[6] = {10, 5, -4, 8, 5, 1}
// int *ptr = 0xffe8
// int *ptr2 = 0xffe8