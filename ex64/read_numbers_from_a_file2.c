#include <stdio.h>

int main(void) {
    FILE    *ifile;
    int     i, N;
    double  num, total;
    
    total = 0;
    ifile = fopen("studentGrades.txt", "r");
    
    fscanf(ifile, "%d", &N);
    
    for (i = 0; i<N; i++) {
        fscanf(ifile, "%lf", &num);
        total = total + num;
    }
    
    printf("%.2lf", total/N);

    fclose(ifile);
    
    return 0;
}