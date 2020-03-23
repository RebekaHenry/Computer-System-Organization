/*
 * hash_table.h - Hash table ADT header file
 *
 * Refactored by: Roy Kravitz (roy.kravitz@pdx.edu)
 * Author:  <your name goes here>
 * 
 * This is the header file for constants, variables, and function prototypes
 * for functionality in the Hash table ADT    
 *
 * This file, and its associated source code file (including the functions that you
 * need to provide) are generated from the code provided by James Routley in his excellent
 * tutorial on Hash tables and hashing (https://github.com/jamesroutley/write-a-hash-table).
 *
 * NOTE:  The Hash table ADT is a clone of James Routhly's code except I refactored it
 * for ECE 361 HW #4 and the teamInfo struct used for the MLS app in HW #3
 *
 * CAVEAT:  I did not implement Routhley's algorithms and code for resizing the Hash table.
 * Instead I made the hash table (hopefully)large enough to hold all of the teams in the team info
 * file with about 60%loading.  It would not be that much extra work to add in his support for
 * resizing the Hash table but like so many professors before me, I will leave that as an exercise
 * for the interested reader.
 */

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

// constants
#define HASH_TABLE_SIZE		85
#define HT_PRIME_1			151
#define HT_PRIME_2			193

#include "teamInfo_orig.h"

// struct containing key:value (k:v) pairs
typedef struct ht_item {
    char* key;
    TeamInfoPtr_t value; //pointer to the value of tir
} ht_item, *hash_ptr, *HashPtr;

// struct containing the hash table
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;


// API function prototypes
ht_hash_table* ht_new(void);				// creates a new hash table
void ht_del_hash_table(ht_hash_table* ht);	// deletes a hash table
HashPtr createKey(TeamInfoPtr_t tir, HashPtr keys[]);
void ht_insert(ht_hash_table* ht, const char* key, TeamInfoPtr_t value); // inserts element into hash table
void* ht_search(ht_hash_table* ht, const char* key);					// searches for element in hash table
void ht_delete(ht_hash_table* ht, const char* key);						// deletes element from hash table
//void displayTeamInfo(ht_hash_table* ht)									//display just the value asked for from table
void ht_dump(ht_hash_table* ht);										// displays entire hast table on terminal

#endif
