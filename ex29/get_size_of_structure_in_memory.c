// Get the size of a structure in memory

//!!! It depends of a compiler. For some compilers it might be a padding. Be careful!

#include <stdio.h>

struct student{
	char firstName[5];
	char lastName[5];
	int birthYear;
	double aveGrade;
};

int main(void) {
    //! showMemory(start=65520)
	struct student me;
    printf("Size of struct student is %zu.\n", sizeof(struct student)); // instead of "struct student" we can type "me"
    printf("Size of firstName is %zu.\n", sizeof(me.firstName));
    printf("Size of lastName is %zu.\n", sizeof(me.lastName));
    printf("Size of birthYear is %zu.\n", sizeof(me.birthYear));
    printf("Size of aveGrade is %zu.\n", sizeof(me.aveGrade));
	return 0;
}

// Terminal
// Size of struct student is 22.    !!! in some compilers it might be 24. Padding
// Size of firstName is 5.
// Size of lastName is 5.
// Size of birthYear is 4.
// Size of aveGrade is 8.