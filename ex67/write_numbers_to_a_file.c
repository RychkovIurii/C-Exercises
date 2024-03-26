// "write numbers to a file using fprintf()"

#include <stdio.h>

int main(void) {
    FILE *ofile;  /* You can use any variable name here, just make sure you 
                     include the '*'. */
    char filename[] = "my_first_output_file.txt";
    int num;
    
    ofile = fopen(filename, "w"); 
     
    do {
        printf("Please enter a grade. Enter -1 to quit: \n");
        scanf("%d", &num);
        if (num != -1)
            fprintf(ofile, "%d ", num);        
    } while (num != -1);
    fclose(ofile);
    
    return 0;
}

/*
#include <stdio.h>

int main(void) {
    FILE *ofile;
    char filename[] = "my_first_output_file.txt";
    int num;

    ofile = fopen(filename, "w");

    printf("Please enter a grade. Enter -1 to quit: \n");
    scanf("%d", &num);

    while (num != -1) {
        fprintf(ofile, "%d ", num);
        printf("Please enter a grade. Enter -1 to quit: \n");
        scanf("%d", &num);
    }

    fclose(ofile);

    return 0;
}
*/