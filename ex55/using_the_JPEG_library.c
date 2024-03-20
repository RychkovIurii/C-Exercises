// Activity: using the JPEG library

//libjpeg.so vizplus.c vizplus

#include <stdio.h>

int main(void){
    printf("gcc -std=c11 -Wall -fmax-errors=10 -Wextra /usr/lib/libjpeg.so vizplus.c -o vizplus");
    return 0;
}