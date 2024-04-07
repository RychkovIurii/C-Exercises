#include <stdio.h>

// #	##
#define SQ_PR(A, B) ((A) * (B))
#define TEXT(A, B) "Square of rectangle (" #A ") * (" #B ")\n"	//like a casting
#define X_N(N) x ## N

int main(void)
{
	int res = SQ_PR(2, 3);

	printf("res = %d\n", res);		// res = 6

	printf(TEXT(x-2, y-3));			// Square of rectangle (x-2) * (y-3)

	int x1 = 1, x2 = -2, x4 = 10;
	printf("%d\n", X_N(4));			// 10

	return 0;
}