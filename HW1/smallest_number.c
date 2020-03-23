#include <stdlib.h>
#include <stdio.h>

/*
	Write a C program that prompts the user to 
	enter a U.S. dollar amount and then shows
	how to pay that amount using the smallest 
	number of $20, $10, $5, and $1 bills

*/

int main(){

	int dollar_amount, number_twenties, number_tens, number_fives, 
	number_ones, reduce_to_next_number, subtraction, number_test_cases;;

	printf("Test Cases Below\n\nEnter the Number of Test Cases: ");
	scanf("%d", &number_test_cases);

	for (int i = 0; i < number_test_cases; i++){
		//47
		scanf ("%d", &dollar_amount);
		printf("Dollar Amount: $%d\n", dollar_amount);

		//checking for twenties

		if (dollar_amount >= 20){
			// 47 / 20 = 2
			number_twenties = dollar_amount / 20;
			// 2 * 20 = 40
			reduce_to_next_number = number_twenties * 20;
			// 47 - 40 = 7
			subtraction = dollar_amount - reduce_to_next_number;
		}

		else {
			number_twenties = 0;
		}

		//checking for tens
		//7 is not greater than 10, so onto next statement
		if (subtraction >= 10){
			number_tens = subtraction / 10;
			reduce_to_next_number = number_tens * 10;
			subtraction = subtraction - reduce_to_next_number;
		}
		else {
			number_tens = 0;
		}

		//checking for fives
		//7 is greater than 5
		if (subtraction >= 5){
			//7 / 5 = 1
			number_fives = subtraction / 5;
			//1 * 5 = 5
			reduce_to_next_number = number_fives * 5;
			// 7 - 5 = 2
			subtraction = subtraction - reduce_to_next_number;

		}
		else{
			number_fives = 0;
		}


		//checking for ones
		//2 is greater than 1
		if (subtraction >= 1){
			// 2 / 1 = 1
			number_ones = subtraction / 1;
			// 1 * 1 = 1
			reduce_to_next_number = number_ones * 1;
			// 2 - 1 = 1
			subtraction = subtraction - reduce_to_next_number;
		}
		else{
			number_ones = 0;
		}

			printf("Number of Twenties: %d\nNumber of Tens: %d\nNumber of Fives: %d\nNumber of Ones: %d\n\n", 
				number_twenties, number_tens, number_fives, number_ones);

		}


	



	

}