/**
 *Author: <Rebeka Henry>
 *Program: SortingColors
 *Write an application that makes use of the qsort() and bsearch() 
 *C standard library functions that returns the 24-bit color value 
 *for the named color. That is, brown is the key and #AA5500 is the 
 *“value” for CGA color 6. The program should query the user for a 
 *color and return the 24-bit value for the color. As with the application 
 *in Part 1, the program should loop, prompting the user for additional records 
 *to look up, until the user enters an empty line (just the Enter key).
 *
 *0 = black -> #000000
 *1 = blue -> #0000AA
 *2 = green -> #00AA00
 *3 = cyan -> #00AAAA
 *4 = red -> #AA0000
 *5 = magenta -> #AA00AA
 *6 = brown -> #AA5500
 *7 = light gray -> #AAAAAA
 *8 = dark gray -> #555555
 *9 = light blue -> #5555FF
 *10 = light green -> #55FF55
 *11 = light cynan -> #55FFFF
 *12 = light red -> #FF5555
 *13 = light magenta -> #FF55FF
 *14 = yellow -> #FFFF55
 *15 = white -> #FFFFFF
 *
 *
 *Algorithm
 *
 *Place the keys (colors) in an array of pointers
 *
 *Prompt user for input
 *
 *Sort the keys (colors) using qsort
 *
 *Search for a key (color) using bsearch
 *
 *If the user input matches the key (color) in the sorted values, display the hex value
 *
 *
 *
 *List of sources listed below
 *
 *The C Programming Language By Brian W. Kernighan and Dennis M. Ritchie. 1988
 *
 *http://icarus.cs.weber.edu/~dab/cs1410/textbook/8.Strings/qsort.html
 *
 *https://www.codingunit.com/c-reference-stdlib-h-function-bsearch
 *
 *https://www.cs.bu.edu/teaching/c/string/intro/
 *
 *https://www.tutorialspoint.com/c_standard_library/c_function_bsearch.htm
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int charComparator (const void * a, const void * b)
{
 	 char **ia = (char **)a;
   	 char **ib = (char **)b;
    return strcmp(*ia, *ib);
}


int main(){

	//insert the colors into the array
	char *colors []= {"black", "blue", "green", "cyan", "red", "magenta", "brown", 
		"light gray", "dark gray", "light blue", "light green", "light cyan", 
		"light red", "light magenta", "yellow", "white"};

	//get user input and call the SortSearch function
	printf("Type a CGA color in lowercase letters. To quit, type quit and the ENTER key\n");

	while(1){
		char userKey[256] = {};
		fgets(userKey, sizeof(userKey), stdin);
		//remove new line char
		for (int i=0; i < 256; i++)
			if (userKey[i] == '\n')
				userKey[i] = '\0';

		//if user hits quit, the exit the program
		if (strcmp(userKey,"quit") == 0){
			break;
		}
		else{
			//sort the colors
			qsort(colors, 16, sizeof(colors[0]), charComparator);

			for (int i = 0; i < sizeof(colors)/sizeof(char*); i++){
				//display the sorted colors
				printf("Colors %s\n", colors[i]);
			}
			printf("\n\n");
			//assign the user input to a pointer to key
			char *key = userKey;
			//this pointer to pointer will search for the desired key
			char **searchKey;

			searchKey = (char**)bsearch(&key, colors, 16, sizeof(colors[0]), charComparator);
			//if the key exists, then use the pointer to pointers to display the key
			//display the value associated with the key

			if (*searchKey != NULL){
				printf("Key: %s\n", *searchKey);
				if(*searchKey == "black"){
					printf("Value: #000000\n\n");
				}
				if(*searchKey == "blue"){
					printf("Value: #0000AA\n\n");
				}
				if(*searchKey == "green"){
					printf("Value: #00AA00\n\n");
				}
				if(*searchKey == "cyan"){
					printf("Value: #00AAAA\n\n");
				}
				if(*searchKey == "red"){
					printf("Value: #AA0000\n\n");
				}
				if(*searchKey == "magenta"){
					printf("Value: #AA00AA\n\n");
				}
				if(*searchKey == "brown"){
					printf("Value: #AA5500\n\n");
				}
				if(*searchKey == "light gray"){
					printf("Value: #AAAAAA\n\n");
				}
				if(*searchKey == "dark gray"){
					printf("Value: #555555\n\n");
				}
				if(*searchKey == "light blue"){
					printf("Value: #5555FF\n\n");
				}
				if(*searchKey == "light green"){
					printf("Value: #55FF55\n\n");
				}
				if(*searchKey == "light cyan"){
					printf("Value: #55FFFF\n\n");
				}
				if(*searchKey == "light red"){
					printf("Value: #FF5555\n\n");
				}
				if(*searchKey == "light magenta"){
					printf("Value: #FF55FF\n\n");
				}
				if(*searchKey == "yellow"){
					printf("Value: #FFFF55\n\n");
				}
				if(*searchKey == "white"){
					printf("Value: #FFFFFF\n\n");
				}
			}
			else{
				printf("Key %s not found\n", userKey);
			}	
		}
	}

	return 0;
}