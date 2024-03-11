// Define and use structures

#include <stdio.h>

struct student{
    char firstName[30];
    char lastName[30];
    int birthYear;
    double aveGrade;
};

int main(void) {
	//! showMemory(start=65520)
    struct student me = {"Iurii", "Rychkov", 1989, 3.5};
    printf("Name: %s %s\n", me.firstName, me.lastName);
    printf("Year of birth: %d\n", me.birthYear);
    printf("Average grade: %.2lf\n", me.aveGrade);
	return 0;
}