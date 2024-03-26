#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int plants;
    double price;

    if (argc == 3){
        plants = atoi(argv[1]);
        price = atof(argv[2]);
        printf("%d plants for %.2lf dollars each cost %.2lf dollars.", plants, price, plants * price);
    }
    else{
        printf("Invalid input.");
    }
    return 0;
}