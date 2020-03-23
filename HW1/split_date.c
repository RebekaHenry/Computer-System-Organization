/*	day_of_year is an integer between 1 and 366, 
	specifying a particular day within the year
	designated by the parameter year. 
	month and day point to variables in which 
	the function will store the equivalent 
	month (1 – 12) 
	and day within the month (1 – 31)

*/

#include <stdio.h>
#include <stdlib.h>

//size of char array
#define SIZE 10
#define SIZE2 3

/*The function below splits the day of the year, the year, the month, and the day. It incorporates
  Zeller's rule which can be used to find out the day in the year (i.e. Friday, Saturday, Sun, etc)
  F = (k + ((13 * M)-1)/ 5 + D + D/4 + C/4 - 2*C) % 7
  k = day
  M = month(march is 1 and February is 12)
  D = last two digits of the year (1990 -> 90)
  C = firt two digits of the year (1990 -> 19)

  */


void split_date(int day_of_year, int year, int *month, int *day){

	
	int last_two_digits, first_two_digits, compute_the_day_of_week, 
		thirteen_M, D_by_four, C_by_four, two_C;

	char *day_week[SIZE];
	char *name_month[SIZE2];
	

	//D
	last_two_digits= year % 100;
	//C
	first_two_digits = year / 100;

	//compute the month to fit the rule
	if (*month == 1){
		*month = 11;
		*name_month = "JAN";
	}
	else if (*month == 2){
		*month = 12;
		*name_month = "FEB";
	}
	else if (*month == 3){
		*month = 1;
		*name_month = "MAR";
	}
	else if (*month == 4){
		*month = 2;
		*name_month = "APR";
	}
	else if (*month == 5){
		*month = 3;
		*name_month = "MAY";
	}
	else if (*month == 6){
		*month = 4;
		*name_month = "JUN";
	}
	else if (*month == 7){
		*month = 5;
		*name_month = "JUL";
	}
	else if (*month == 8){
		*month = 6;
		*name_month = "AUG";
	}
	else if (*month == 9){
		*month = 7;
		*name_month = "SEP";
	}
	else if (*month == 10){
		*month = 8;
		*name_month = "OCT";
	}
	else if (*month == 11){
		*month = 9;
		*name_month = "NOV";
	}
	else if (*month == 12){
		*month = 10;
		*name_month = "DEC";
	}
	
	//The rule broken down below
	//(13 * M)-1)/ 5
	thirteen_M = (13*(*month)-1)/5;
	// D / 4
	D_by_four = last_two_digits / 4;
	//C / 4
	C_by_four = first_two_digits / 4;
	// 2 * C
	two_C = 2 * first_two_digits;

	compute_the_day_of_week = (((((*day) + thirteen_M) + last_two_digits + D_by_four + C_by_four) - two_C) % 7);


	if (compute_the_day_of_week == 0){
		*day_week = "Sunday";
	}
	else  if (compute_the_day_of_week == 1){
		*day_week = "Monday";
	}
	else if (compute_the_day_of_week == 2){
		*day_week = "Tuesday";
	}
	else if (compute_the_day_of_week == 3){
		*day_week = "Wednesday";
	}
	else if (compute_the_day_of_week == 4){
		*day_week = "Thursday";
	}
	else if (compute_the_day_of_week == 5){
		*day_week = "Friday";
	}
	else if (compute_the_day_of_week == 6){
		*day_week = "Saturday";
	}

	
	//print day of the week
	printf("Day of Year: %d for %d-%s-%d falls on a %s\n", 
		   day_of_year, *day, *name_month, year, *day_week);
}


int main(){

	int month_value, day_value;

	month_value = 10;
	day_value = 10;

	split_date(283, 2019, &month_value, &day_value);


	return 0;
}