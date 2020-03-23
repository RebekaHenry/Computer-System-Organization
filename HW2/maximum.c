#include <stdio.h>

/*
	recursively finds the largest integer between list[0] and list[n]. 
	Assume at least one element is in the list. Test it with a main program 
	(you write this program) that takes as input an integer count followed by 
	the values. Your test program should try several cases besides the sample 
	given below. You may “hardwire” the integer counts and value lists into 
	your program instead of using scanf()if you prefer. Output the original values 
	followed by the maximum number in the list. Do not use a loop in maximum().

	Sample Input:
	5 50 30 90 20 80
	
	Sample Output:
	Original list: 50 30 90 20 80 
	Largest value: 90

	accessing elements

	20 30 90 70 80

	5-1 = 80
	5-2 = 70
	5-3 = 90
	5-4 = 30
	5-5 = 20

	[n-1] for recursive calls

	normally would have done this with a loop:

	temp = 0
	for (int i = 0; i < n, i++){
		if (list[i] > temp){
			temp = list[i]
		}
	}
	
	BUT since it's recursion, we want to
	compare it with the term at that value
	for the next call until we get the max
	term. so include the temp variable 
	but make sure that holds the previous call
	term
	

	what we want to do is check the size of the array


	
*/
int maximum (int list[], int n){

	int temp;

	//traversing array
	if (n == 1){
		return list[0];
	}

	//similar to list[i] but init with that starting val
	temp = maximum(list, n-1);
	//list[i] > temp
	if (list[n-1] > temp){
		//temp = list[i]
		temp = list[n-1];
	}
	//return the value at that point of the call
	return temp;

}

int main(){

	//n = 10
	int arr[] = {14,3,1,11,100,109,118,20,500,345};
	//n = 7
	//int arr[] = {29,1023,47,50,43331,32};
	//n = 6
	//int arr[] = {70, 1000, 90, 50, 24};
	//n = 6 
	//int arr[] = {20, 30, 90, 70, 80};


	printf("Original List: ");

	//sizeof(arr)/sizeof(int) because we don't want it to decay to a pointer
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++){
		printf("%d ", arr[i]);
	}
	printf("\nLargest Value: %d\n", maximum(arr, 10));

	return 0;
}

