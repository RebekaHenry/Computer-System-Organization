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
 */

// include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "teamInfo_orig.h"
#include "hash_table.h"


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
        case CONF_OTHER:	strcpy(conf_ptr, "OTHER");     break;
        case CONF_EASTERN:	strcpy(conf_ptr, "EASTERN");   break;
        case CONF_WESTERN:	strcpy(conf_ptr, "WESTERN");   break;
        case CONF_NWSL:		strcpy(conf_ptr, "NWSL");      break;

        default:			strcpy(conf_ptr, "?????");     break;
    }
    return conf_ptr;
}


/**
 * code below is the old get_league_str() commented out
 * get_league_str() - returns a string containing the league the team plays in.
 * Assumes that sufficient space has been allocated for the return string
 *
 * @param league   (int) league the team plays in
 *
 * @returns         a pointer to a char array holding the league the team plays in
 */
/*char* get_league_str(int league)
{
	static char league_ptr[MAX_LEAGUE_TXT];	// string containing name of league.
											// static so it hangs around after function returns
    switch (league)
    {
        case LEAGUE_OTHER:	strcpy(league_ptr, "OTHER");   break;
        case LEAGUE_MLS:	strcpy(league_ptr, "MLS");     break;
        case LEAGUE_NWSL:	strcpy(league_ptr, "USL");     break;
        case LEAGUE_USL:	strcpy(league_ptr, "NWSL");    break;

        default:			strcpy(league_ptr, "?????");   break;
    }
    return league_ptr;
}*/

/**
 * Code below is the new get_league_str function. It has been changed from static so that
 * it can be used for my application.
 * get_league_str() - returns a string containing the league the team plays in.
 * Assumes that sufficient space has been allocated for the return string
 *
 * @param league   (int) league the team plays in
 *
 * @returns a pointer to a char array holding the league the team plays in
 */
char* get_league_str(int league)
{
	static char league_ptr[MAX_LEAGUE_TXT];	// string containing name of league.
											// static so it hangs around after function returns
    switch (league)
    {
        case LEAGUE_OTHER:   strcpy(league_ptr, "OTHER");   break;
        case LEAGUE_MLS:     strcpy(league_ptr, "MLS");     break;
        case LEAGUE_NWSL:    strcpy(league_ptr, "NWSL");    break;
        case LEAGUE_USL:	 strcpy(league_ptr, "USL");     break;

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
 * @returns         the pointer to the team information record that was created
 *
 * @note You may have to include part (or all) of the absolute path in the file name.  It depends
 * on what directory(s) you are building and running your application from
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
*
* @param teamInfoPtr    (pointer to the team record) being examined
*
* This function is used to display one record in the main function after user is prompted
* and provides the correct key
* @returns          nothing
*/
void displayTeamInfo(TeamInfoPtr_t teamInfoPtr)
{
	//display a record
	printf("Name: %s\nNickname: %s\nLeague: %s\nConference: %s\nWins: %d\nLosses: %d\nDraws:%d\n", 
		teamInfoPtr->name,teamInfoPtr->nickname, get_league_str(teamInfoPtr->league) , 
		get_conf_str(teamInfoPtr->conf),teamInfoPtr->wins, teamInfoPtr->losses, teamInfoPtr->draws);

	printf("\n\n");

}



