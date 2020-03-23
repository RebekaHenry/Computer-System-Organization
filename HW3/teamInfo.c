/*
 * teamInfo.c - Team info source code file for mls app
 *
 * Originator: Roy Kravitz (roy.kravitz@pdx.edu)
 * Author:  <Rebeka Henry>
 * 
 * This is the source code file that for functionality specific to the Team Info database that
 * is part of an ECE 361 homework assignment.    
 *
 * This file, and its associated header file (including the functions that you
 * need to provide) are meant to be used by your Linked List ADT and main() to deliver
 * the functionality required in the assignment
 *
 * @note:  You need to provide the code for several of these functions

 * Source on How to initialize character array from char pointer
 * https://stackoverflow.com/questions/25110302/c-initialize-character-array-from-character-pointer
 */

// include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "teamInfo.h"
#include "teamInfo_LinkedList.h"

// constants
#define MAX_TEAMS 100
#define NUM_OF_FIELDS_PER_RECORD 7

/**
 * Creates a new Team Info record
 *
 * @param name      (pointer to a char[]) containing the name of the team
 * @param nickname  (pointer to a char[]) containing the nickname of the team
 * @param league    (int) containing the league the team plays in (MLS, NWSL, USL, Other)
 * @param conf      (int) containing the conference the team plays in (Eastern, Wsstern, NWSL, Other}
 * @param nwins     (int) containing the number of wins during the regular season
 * @param nlosses   (int) containing the number of losses during the regular season
 * @param ndraws    (int) containing the number of draws during the regular season
 *
 * @returns         a pointer to a new TeamInfo record. 
 */
TeamInfoPtr_t createTeamInfoRecord(const char* name, const char* nickname, int league,
					int conf, int nwins, int nlosses, int ndraws)
{
		TeamInfoPtr_t TeamInfo;

		//allocate space for the pointer
		TeamInfo = malloc(sizeof(TeamInfo_t));

		//check to see if space was allocated correctly

		if(!TeamInfo){
			printf("Team information was not allocated correctly\n");
			exit(1);
		}


		//initialize the character array from the character pointer
		memset(TeamInfo->name, '\0', MAX_TEAM_NAME);
		strcpy(TeamInfo->name, name);

		strncpy(TeamInfo->name, name, MAX_TEAM_NAME-1);

		memset(TeamInfo->nickname, '\0', MAX_TEAM_NICKNAME);
		strcpy(TeamInfo->nickname, nickname);

		strncpy(TeamInfo->nickname, nickname, MAX_TEAM_NICKNAME-1);

		//initialize the data fields
		TeamInfo->league = league;
		TeamInfo->conf = conf;
		TeamInfo->wins = nwins;
		TeamInfo->losses = nlosses;
		TeamInfo->draws = ndraws;

		return TeamInfo;
}

// Helper functions

/**
 * get_conf_str() - returns a string containing the conference the team plays. 
 * Assumes that sufficient space has been allocated for the return string
 *
 * @param conf    (int) conference
 *
 * @returns         a pointer to a char array holding the conference the team plays in
 */
static char* get_conf_str(int conf)
{
    static char conf_ptr[MAX_CONF_TXT];	// string containing name of conference. 
									// static so it hangs around after function returns
    switch (conf)
    {
        case CONF_OTHER:     strcpy(conf_ptr, "OTHER");     break;
        case CONF_EASTERN:   strcpy(conf_ptr, "EASTERN");   break;
        case CONF_WESTERN:   strcpy(conf_ptr, "WESTERN");   break;
        case CONF_NWSL:      strcpy(conf_ptr, "NWSL");      break;

        default:             strcpy(conf_ptr, "?????");     break;
    }
    return conf_ptr;
}


/**
 * get_league_str() - returns a string containing the league the team plays in.
 * Assumes that sufficient space has been allocated for the return string
 *
 * @param league   (int) league the team plays in
 *
 * @returns         a pointer to a char array holding the league the team plays in
 */
static char* get_league_str(int league)
{
	static char league_ptr[MAX_LEAGUE_TXT];	// string containing name of league.
											// static so it hangs around after function returns
    switch (league)
    {
        case LEAGUE_OTHER:   strcpy(league_ptr, "OTHER");   break;
        case LEAGUE_MLS:     strcpy(league_ptr, "MLS");     break;
        case LEAGUE_USL:     strcpy(league_ptr, "USL");     break;
        case LEAGUE_NWSL:    strcpy(league_ptr, "NWSL");    break;

        default:             strcpy(league_ptr, "?????");   break;
    }
    return league_ptr;
}


/**
 * readTeamInfo() - reads the team info from a file
 * and creates an array of pointers to team Info records
 *
 * @param fname     (pointer to char[]) file name of  team info file to read
 * @param teams     (pointer to array of team info records) array to put pointers to team records into
 *
 * @returns         a the number of records
 *
 * This function will be used to insert into the list after the list is created
 * This function will also display all of the data from the teamInfo.txt
 */
TeamInfoPtr_t readTeamInfo(char* fname, TeamInfoPtr_t  teams[])
{
    FILE *fp;           // pointer to team info file
    char buf[100];      // input buffer

    // holding variables for fields in the team info record
    char tir_name[MAX_TEAM_NAME];
    char tir_nickname[MAX_TEAM_NICKNAME];
    int tir_league;
    int tir_conf;
    int tir_wins;
    int tir_losses;
    int tir_draws;

    int nfields = 0;		// number of fields read from file
    int nrecs = 0;          // number of records
    TeamInfoPtr_t tir;		// pointer to team info record

    // open the team info file for reading
    if ((fp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "readTeamInfo: Could  not open team info file: %s (%s)...exiting\n",
			fname, strerror(errno));
        exit(1);
    }

	tir = (TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));
	if (!tir) {
		fprintf(stderr, "readTeamInfo: Could not create Team Info record...exiting\n");
		exit(1);
	}
	
	// ready to read team info records
    printf("readTeamInfo: Reading team info file...\n");

    // get record from team info file
    while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		buf[strlen(buf) - 1] = '\0';    // trim the string
		if ((buf[0] == '/') && (buf[1] == '/'))  {
			// this is a comment, display and skip it
			printf("%s\n", buf);
		}  // display and skip comments
		else {  // try to process a team info record
			if (strlen(buf) > 0) {  // is it a blank line?
				// use scanf() to parse the team info line in the file
				nfields = sscanf(buf, "%30s %5s %d %d %d-%d-%d",
					tir_name, tir_nickname, &tir_league, &tir_conf,
					&tir_wins, &tir_losses, &tir_draws);

				if (nfields != NUM_OF_FIELDS_PER_RECORD) {  // is the team info line valid?
					// error parsing the line
					fprintf(stderr,
					"readTeamInfo: Error parsing team info record: #fields read = %d\tline=%s\n",
					nfields, buf);
					fprintf(stderr,
  					  "name= %s\tnickname= %s\tleague= %d\tconference= %d\twins-losses-ties= %d-%d-%d\n",
					tir_name, tir_nickname, tir_league, tir_conf, tir_wins, tir_losses, tir_draws);
				}  // invalid team info line - wrong number of fields
				else {  // add the record to the array of teams				
					// replace underscores ('_') with space in the team name
					for(int i = 0; i < strlen(tir_name); i++) {
						if (tir_name[i] == '_') {
							tir_name[i] = ' ';
						}
					}
					// create a new team info record and add it to the array
					tir = createTeamInfoRecord(tir_name, tir_nickname, tir_league, tir_conf, tir_wins,
						tir_losses, tir_draws);
					teams[nrecs] = tir;

					printf("readTeamInfo: Added record %d\n", nrecs);
					
					nrecs++;

					
				} // right number of fields - add team info record to array
			} // not an empty line
		} // try to process a team info record
    } // read all of the line of the file
    fclose(fp);
    printf("\n\n");


    return tir;
}

/**
* Displays the information from a team record on stdout
* It calls the readTeamInfo function to get the team information record
* @param teamInfoPtr    (pointer to the team record) being examined
*
* @returns          nothing
*/
void displayTeamInfo(TeamInfoPtr_t teamInfoPtr)
{

	TeamInfoPtr_t teams[24];

	//read the information from the file
	teamInfoPtr = readTeamInfo("teamInfo.txt", teams);


	//display the entire record
	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){
		printf("%30s %5s %d %d %d-%d-%d\n", teams[i]->name, 
		teams[i]->nickname, teams[i]->league, teams[i]->conf, 
		teams[i]->wins, teams[i]->losses, teams[i]->draws);
	}

	printf("\n\n");


}


/*
 * It calls the getTeamInfoRecord function to get the record at a specific point

 * It calls the createLList function and the insertNodeInLList function to create 
 * the list and to insert the pointer to the list

 * the main function should display all of the teams by conference

 * Find and display the 5 teams with the best winning percentages in 2019 
 * [wins / (wins + losses + draws)] no matter which conference they are in.

 * Display the team with the most wins and the team with the most losses in each
 * conference.
*/

int main(){

	TeamInfoPtr_t teamInfoPtr;

	TeamInfoPtr_t record;

	record = (TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));

	teamInfoPtr = malloc(sizeof(TeamInfo_t));

	LinkedListPtr_t L;

	TeamInfoPtr_t teams[24];

	//display the entire record
	displayTeamInfo(teamInfoPtr);

	//create the list
	L = createLList();

	//read the information from the file
	teamInfoPtr = readTeamInfo("teamInfo.txt", teams);


	//insert each record into the linked list by looping through the teams array
	
	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){
		//insert the record into the list to head of the list
		insertNodeInLList(L, teams[i], 1);
	}
	
	/*function returns pointer to the team information record at a particular position

	   Conference
	   1 = Eastern
	   2 = Western
	   3 = NWSL
	   0 = OTHER

	   League
	   1 = MSL
	   2 = NWSL
	   3 = USL
	   0 = OTHER

	*/

	//if Western Conference
	record =  getTeamInfoRecord(L, 0);

	printf("%20s (%s)\n\n", get_league_str(record->league), get_conf_str(record->conf));

	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		switch(record->conf){
			
			//EASTERN
			case 1:
				//printf("%s\n", record->name);
			break;	
			//WESTERN
			case 2:
				printf("%30s\n", record->name);
			break;
			//NWSL
			case 3:
				
				printf("%30s\n", record->name);
			break;

			//OTHER
			case 0:
				printf("%30s\n", record->name);
			break;

			default:
				printf("Conference is not present");
			break;				

		}
	}

	printf("\n\n");
	//if eastern conference

	record =  getTeamInfoRecord(L, 23);

	printf("%20s (%s)\n\n", get_league_str(record->league), get_conf_str(record->conf));


	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		switch(record->conf){
			
			//EASTERN
			case 1:
				printf("%30s\n", record->name);
			break;	
			//WESTERN
			case 2:
				//printf("%s\n", record->name);
			break;
			//NWSL
			case 3:
				
				printf("%30s\n", record->name);
			break;

			//OTHER
			case 0:
				printf("%30s\n", record->name);
			break;

			default:
				printf("Conference is not present");
			break;				

		}
	}

	printf("\n\n");

	/*display the five teams with the best winning percentages
	[wins / (wins + losses + draws)]
	Note: in this case, there are 6 teams with the best winning
	percentages if we are talking about greater than 45.5 percent
	Two teams have the same score and that is why they are both included

	Real Salt Lake 47.058823
    Seattle Sounders 47.058823
	*/

 	float w = 0.0;
 	float divi = 0.0;
 	float total = 0.0;

 	printf("Top Five Teams with Best Winning Percentages\n");
	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		w = record->wins;
		divi = record->wins + record->losses + record->draws;

		total = w/divi* 100.00;

		if (total > 45.5){
			printf("%30s %f\n", record->name, total);
		}
	}

	printf("\n\n");

	//Display the team with the most wins and the team with the most losses in each conference
	printf("Western Conference Wins\n");

	//if Western Conference
	record =  getTeamInfoRecord(L, 0);

	printf("%s (%s)\n\n", get_league_str(record->league), get_conf_str(record->conf));

	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		switch(record->conf){
			
			//EASTERN
			case 1:
				//printf("%s\n", record->name);
			break;	
			//WESTERN
			case 2:
				if (record->wins > 20){
					printf("%30s\n", record->name);
				}
				
			break;
			//NWSL
			case 3:
				
				printf("%30s\n", record->name);
			break;

			//OTHER
			case 0:
				printf("%30s\n", record->name);
			break;

			default:
				printf("Conference is not present");
			break;				

		}
	}

	printf("\n\n");


	//Display the team with the most wins and the team with the most losses in each conference
	printf("Western Conference Losses\n");

	//if Western Conference
	record =  getTeamInfoRecord(L, 0);

	printf("%s (%s)\n\n", get_league_str(record->league), get_conf_str(record->conf));

	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		switch(record->conf){
			
			//EASTERN
			case 1:
				//printf("%s\n", record->name);
			break;	
			//WESTERN
			case 2:
				if (record->losses >= 18){
					printf("%30s\n", record->name);
				}
				
			break;
			//NWSL
			case 3:
				
				printf("%30s\n", record->name);
			break;

			//OTHER
			case 0:
				printf("%30s\n", record->name);
			break;

			default:
				printf("Conference is not present");
			break;				

		}
	}

	printf("\n\n");

	//if eastern conference
	printf("Eastern Conference Wins\n");

	//if Eastern Conference
	record =  getTeamInfoRecord(L, 23);
	printf("%s (%s)\n\n", get_league_str(record->league), get_conf_str(record->conf));

	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		
		switch(record->conf){
			
			//EASTERN
			case 1:
				if (record->wins >= 18){
					printf("%30s\n", record->name);
				}
			break;	
			//WESTERN
			case 2:
				//printf("%s\n", record->name);
			break;
			//NWSL
			case 3:
				
				printf("%30s\n", record->name);
			break;

			//OTHER
			case 0:
				printf("%30s\n", record->name);
			break;

			default:
				printf("Conference is not present");
			break;				

		}
	}

	printf("\n\n");

	//if eastern conference
	printf("Eastern Conference Losses\n");

	//if Eastern Conference
	record =  getTeamInfoRecord(L, 23);
	printf("%s (%s)\n\n", get_league_str(record->league), get_conf_str(record->conf));

	for (int i = 0; i < sizeof(teams)/sizeof(TeamInfoPtr_t); i++){

		record =  getTeamInfoRecord(L, i);

		
		switch(record->conf){
			
			//EASTERN
			case 1:
				if (record->losses >= 18){
					printf("%30s\n", record->name);
				}
			break;	
			//WESTERN
			case 2:
				//printf("%s\n", record->name);
			break;
			//NWSL
			case 3:
				
				printf("%30s\n", record->name);
			break;

			//OTHER
			case 0:
				printf("%30s\n", record->name);
			break;

			default:
				printf("Conference is not present");
			break;				

		}
	}

	printf("\n\n");


	return 0;
}
