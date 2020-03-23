#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "teamInfo_orig.h"
#include "hash_table.h"

int main(){

	TeamInfoPtr_t teams[NUM_TEAMS];

	readTeamInfo("teamInfo2.txt", teams);

	ht_hash_table* teams_ht;

	ht_item* key;


	HashPtr keys[NUM_TEAMS] = {};

	//create all the keys from the nickname and league
	for (int i = 0; i < NUM_TEAMS; i++){
		key = createKey(teams[i], keys);
	}

	//create the hash table
	teams_ht = ht_new();

	//insert into the hash table

	for (int i = 0; i < NUM_TEAMS;i++){
		//insert team records and keys into hash_table
		ht_insert(teams_ht, keys[i]->key, keys[i]->value);
	}

	//get user input now that all key and values have been inserted into the hash table
	printf("Enter the League and NickName on one Line CAPITALIZED. To quit, type quit and the ENTER key\n");

	while(1){
		char userInput[256] = {};
		fgets(userInput, sizeof(userInput), stdin);
		//remove new line char
		for (int i=0; i < 256; i++)
			if (userInput[i] == '\n')
				userInput[i] = '\0';

		//if user hits quit the exit the program
		if (strcmp(userInput,"quit") == 0){
			break;
		}
		else{

			//search for the key
				TeamInfoPtr_t teamptr = NULL;
				teamptr = (TeamInfoPtr_t) ht_search(teams_ht, userInput);
				if (teamptr == NULL){
					printf("No Team Found\n");
				}
				else{
					displayTeamInfo(teamptr);
				}
		}
	}

	//display the entire hash table to show that all keys were correctly assigned to all values
  	ht_dump(teams_ht);
    
    return 0;
}