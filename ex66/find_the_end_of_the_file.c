#include <stdio.h>

int main(void) {
    FILE *ifile;  
    double num, max;
    int class;
    
    ifile = fopen("gradeComparison.txt", "r"); 
                                
    class=0;
    max = 0;
    
    while (fscanf(ifile, "%lf", &num) != EOF) {
        if (class == 0){
            max = num;
        }
        else if (max < num){
            printf("No %d", class + 1);
            fclose(ifile);
            return 0;
        }
        class++;
    }
    printf("Yes");
    fclose(ifile);
    return(0);
}