#include <stdio.h>

int main(void) {
    FILE *ifile;  
    int num, last_num, check;

    last_num = -1;
    scanf("%d", &check);
    ifile = fopen("myGrades.txt", "r");
    if (ifile == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    while (fscanf(ifile, "%d", &num) != EOF){
        last_num = num;
    }
    fclose(ifile);
    if (last_num == check) {
        return 0;
    }
    ifile = fopen("myGrades.txt", "a");
    if (ifile == NULL) {
        printf("Error opening the file for appending.\n");
        return 1;
    }
    fprintf(ifile, " %d", check);
    fclose(ifile);   
    ifile = fopen("myGrades.txt", "r"); 
    while (fscanf(ifile, "%d", &num) != EOF) {
        printf("%d ", num);
    }
    fclose(ifile);
    return(0);
}