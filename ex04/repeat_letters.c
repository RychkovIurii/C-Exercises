#include <stdio.h>

int main(void){
    int match = 0;
    int len, j;
    int i = 0;
    char word[51];

    scanf("%s", word);
    while (word[i]){
        i++;
    }
    len = i;

    for (i = 0; i < len-1; i++) {
        for (j = 0; j < len-i-1; j++) {
            if (word[j] > word[j+1]) {
                char temp = word[j];
                word[j] = word[j+1];
                word[j+1] = temp;
            }
        }
    }
    for (i = 0; i < len-1; i++) {
        if (word[i] == word[i+1]) {
            match++;
            while (i < len-1 && word[i] == word[i+1]) {
                i++;
            }
        }
    }
    printf("%d", match);
    return 0;
}