#include <stdio.h>

struct date {
        int year;
        int month;
        int day;
    };

/* function prototypes */
void printDate(struct date);
void readDate(struct date *);
struct date advanceDay(struct date); 

int main(void) {
	struct date today, tomorrow;
	readDate(&today);
	printDate(today);
	tomorrow = advanceDay(today);
	printDate(tomorrow);
	return 0;
}

void readDate(struct date *todayptr){
    scanf("%d %d %d", &(*todayptr).year, &(*todayptr).month, &(*todayptr).day);
}

void printDate(struct date today){
    printf("%02d/%02d/%04d\n", today.month, today.day, today.year);
}

struct date advanceDay(struct date today){
    struct date tomorrow;
    tomorrow.day = today.day + 1;
    tomorrow.month = today.month;
    tomorrow.year = today.year;
    if (tomorrow.day > 28 && today.month == 2){
        tomorrow.day = 1;
        tomorrow.month = 3;
    }
    else if (tomorrow.day > 31 && ((today.month % 2 == 1 && today.month < 9) || today.month) == 10){
        tomorrow.day = 1;
        tomorrow.month = today.month + 1;
    }
    else if (tomorrow.day > 31 && today.month == 12){
        tomorrow.day = 1;
        tomorrow.month = 1;
        tomorrow.year = tomorrow.year + 1;
    }
    else if (tomorrow.day == 31 && ((today.month % 2 == 0 && today.month < 7) || today.month == 9 || today.month == 11)){
        tomorrow.day = 1;
        tomorrow.month = today.month + 1;
    }
    return(tomorrow);
}

//if n % 4 == 0 and n % 100 != 0 or n % 400 == 0: