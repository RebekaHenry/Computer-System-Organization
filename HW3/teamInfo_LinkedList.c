/*
 * LinkedList.c - Linked List ADT
 *
 * Originator: Roy Kravitz (roy.kravitz@pdx.edu)
 * Author:  <Rebeka Henry>
 * 
 * This is the source code file for a Linked List ADT that
 * implements a singly linked list.  I've tried to define the
 * API in a way that we can change implementations but keep
 * the API the same
 *
 * @note Code is based on DynamicStack.c from Narasimha Karumanchi
 * @note Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 *
 * @note Prints messages to stdio.  This is Karumanchi's doing
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include "teamInfo_LinkedList.h"

// API functions

/**
 * Creates a new instance of the Linked List
 *
 * @returns	Pointer to the new Linked List instance if it succeeds.  NULL if it fails
 */
LinkedListPtr_t createLList(void) {
	LinkedListPtr_t L = (LinkedListPtr_t) malloc(sizeof(LinkedList_t));
	if(!L) 
		return NULL;
	L->head = NULL;
	L->count = 0;
	return L;
}

/**
 * Returns the number of items in the list
 * 
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	Returns the number of nodes in the linked list
 */
int LListLength(LinkedListPtr_t L){
	return L->count;
}


/**
 * Inserts a new node into the linked list
 * 
 * @param L is a Pointer to a LinkedList instance
 * @param data is the data item to put into the ndw node
 * @param pos is the position in the list to insert the item
 *
 * @returns	void
 */
void insertNodeInLList(LinkedListPtr_t L, TeamInfoPtr_t information, int pos){
	ListNodePtr_t head = L->head;
	ListNodePtr_t q, p;
	ListNodePtr_t newNode = (ListNodePtr_t) malloc(sizeof(ListNode_t));
		
	int k = 1;

	
	if(!newNode){
		printf("LinkedList ADT: Memory Error\n");
		return;
	}

	newNode->data = information;
	p = head;
	if ((pos == 1) || (p == NULL)){
		newNode->next = head;
		L->head = newNode;
		L->count++;
	}
	else {
	
			while((p != NULL) && (k < pos)){
			k++;
			q = p;
			p = p->next;
		}
		newNode->next = q->next;
		q->next = newNode;
		L->count++;
		
	}
}


/**
 * Deletes a new node into the linked list
 * 
 * @param L is a Pointer to a LinkedList instance
 * @param pos is the position in the list to insert the item
 *
 * @returns	void
 */
void deleteNodeFromLLinkedList(LinkedListPtr_t L, int pos) {
	ListNodePtr_t head = L->head;
	ListNodePtr_t q, p;
	
	int k = 1;
	
	p = head;
	if(head == NULL){
		printf("LinkedList ADT: List Empty\n");
		return;
	}
	else if( pos == 1){
		L->head = head->next;
		free(p);
		L->count--;
	}
	else {
		while((p!=NULL) && (k < pos)){
			k++;
			q = p;
			p = p->next;
		}
		if(p == NULL){
			printf("LinkedList ADT: Position does not exist\n");
		}
		else{
			q->next = p->next;
			free(p);
			L->count--;
		}

	}
}


/**
 * Prints all of the data items in the Linked List
 * 
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	void
 */
void printLList(LinkedListPtr_t L) {
	
	ListNodePtr_t head = L->head;
	TeamInfoPtr_t display;

	display = malloc(sizeof(TeamInfo_t));

	display = head->data;
	
	while(head != NULL){
		printf("%s\n", display->name);
		head = head->next;
	}
	printf("\n");
}


/*	returns a pointer to the team information record at a particular position
	supposed to help with traversing the linked list

	Algorithm for returning by position:
		intialize the count struct member

		if the count is equal to the index then return
		the current node

		increment the count

		change current to point to next of the current
		
		source: https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
*/
TeamInfoPtr_t getTeamInfoRecord(LinkedListPtr_t L, int pos){

		ListNodePtr_t head = L->head;

		L->count = 0;

		while(head != NULL){
			if (L->count == pos){
				//pointing to TeamInfoPtr_t data in struct listNode
				return (head->data);
			}
			L->count++;
			head = head->next;
		}
		//this fails if the user asks for an element that isn't there
		assert(0);
}

	


