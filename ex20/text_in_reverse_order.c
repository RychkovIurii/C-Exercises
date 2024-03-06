#include <stdio.h>

int main(void){
    int     i;
    int     amount_of_words = 68;
    int     letters = 41;
    char    text[amount_of_words][letters];

    for (i=0; i<amount_of_words; i++) {
        scanf("%s", text[i]);
    }
    for (i=(amount_of_words - 1); i >= 0; i--) {
        printf("%s ", text[i]);
    }

}