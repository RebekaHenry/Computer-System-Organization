/*	When passed an array a of length n, the function returns a pointer to array’s largest element.

	initialize i and temp (temporary variable)
	i is for traversing the array and getting access to each element
	temp is for comparison

	traverse the array
	for each element in the array a[i], check it with the temporary variable
	if the element is larger than the temporary variable, then point to that element

*/

#include <stdio.h>

int *find_largest(int a[], int n){

	int i, temp;
	int *ptr;

	temp = 0;

	//traversing through array and checking whether the value in 
	//array is greater than the value in temp
	for (int i = 0; i < n; i++){
		if (a[i] > temp){
			//pointing to the array's largest element
			ptr = &a[i];
		}
	}

	return ptr;
}


int main(){

	//testing that the function works
	int a [] = {2,1,9,8,3};

	int *largest = find_largest(a, 5);

	printf("%p\n", &largest);




return 0;
}