#include <stdio.h>

int main() {

    int arr[3] = {15, 16, 17};
    printf("%p\n",arr);
    int * ptr = arr;
    * ptr = 2; // * arr   0R  arr[0]
    * (ptr + 1) = 3; // * (arr + 1)   OR  arr[1]
    * (ptr + 2) = 5;// * (arr + 2)   OR arr[2]
    return 0;
}
// we changed        int arr[3] = {2, 3, 5}

// #Example
// Suppose you have made the following declarations:

// int array[] = {4, 6, 12, -5, -7, 3, 1, 0, -10};
// int *ptr1, *ptr2;
// ptr1 = array+2;
// ptr2 = &ptr1[5];
// What is the value of *(ptr1+1)?
// -5
// What is the value of *(ptr2-3)?
// -7
