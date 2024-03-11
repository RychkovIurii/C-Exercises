#include <stdio.h>

struct date {
        int year;
        int month;
        int day;
    };

void readDate(struct date *);
void printDate(struct date);

int main(void) {
	struct date today;
	readDate(&today);
	printDate(today);
	return 0;
}

void readDate(struct date *todayptr){
    scanf("%d %d %d", &(*todayptr).year, &(*todayptr).day, &(*todayptr).month);
}
void printDate(struct date today){
    if (today.month < 10 && today.day < 10){
        printf("0%d/0%d/%d", today.day, today.month, today.year);
    }
    else if (today.day < 10){
        printf("0%d/%d/%d", today.day, today.month, today.year);
    }
    else if (today.month < 10){
        printf("%d/0%d/%d", today.day, today.month, today.year);
    }
    else
        printf("%d/%d/%d", today.day, today.month, today.year);
}

// printf("%02d/%02d/%04d\n", today.month, today.day, today.year);