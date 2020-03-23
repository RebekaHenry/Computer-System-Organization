/*
	Chief amongst his complaints was that Karumanchi’s 
	algorithm created the head pointer in main() rather 
	than implementing a createList() function in the ADT. 
	As a result, the solution exposed details of the ADT 
	that could have been hidden.

	a. Rewrite the code in SinglyLinked.c 
	(included in the starter repository) to bring 
	the declaration/creation of the head pointer of 
	the list into the ADT. Consider adapting the approach 
	that Karumanchi used in his Stack and Queue examples or 
	you may do as Roy suggested in class and include an array 
	of head pointers in the ADT, returning an index into that 
	array whenever a new linked list (not a node…a new linked list) 
	is created. Your ADT should return an indication of whether the 
	list was created successfully (ex: a NULL pointer or an illegal 
	index like -1 if the create list functionality did not succeed).

	b. (10 pts) Rewrite main() in SinglyLinked.c to use your new ADT. 
	Compile and execute the program. Include your source code and a transcript (log) 
	showing that your new ADT works.



*/

#include<stdio.h>
#include<stdlib.h>

struct listNode{
	int data;
	struct listNode *next;
};

//hiding the head in Linked instead of using listNode
struct Linked{
	struct listNode *head;
};

//implementing Karumanchi's strategy in stack and queue
struct Linked *createList(){
	struct Linked *singLL;
	singLL = malloc(sizeof(struct Linked));

	singLL->head = NULL;
	
	//if the list was not created successfully exit -1
	if(singLL->head == NULL){
		return singLL;
	}
	else{
		exit(-1);
	}	

}

//isEmpty() created like Karumanchi strategy

int isEmpty(struct Linked *singLL){
	return singLL->head == NULL;
}

int singlyListLength(struct Linked *singLL){
	int count=0;
	struct listNode *current;

	if(isEmpty(singLL))
		return 0;
	current = singLL->head;

	while(current!=NULL){
		count++;
		current=current->next;	
	}
	return count;
}

//made a few changes to the insert function
void insertInSinglyLinked(struct Linked *singLL, int data){
	
	struct listNode *newNode;
	newNode = malloc(sizeof(struct listNode));
	if(!newNode){
		printf("Memory Error\n");
		return;
	}
	newNode->data = data;
	newNode->next = singLL->head;
	singLL->head = newNode;
}

//fix this section so that it acts like a linked list
void deleteNodeFromLinked(struct Linked *singLL, int item_to_be_deleted){
	
	struct listNode *temp = singLL-> head;//head node
	struct listNode *prev, *newHead;

	
	//checking if the list is populated
	if(isEmpty(singLL)){
		printf("\nEmpty List\n");
		return;
	}
	//check if the head holds the item to be deleted
	if(temp!= NULL && temp->data == item_to_be_deleted){

		
		newHead = temp->next;
		free(temp);
		singLL->head = newHead;
	}
	

	//search for the item to be deleted by traversing
	while(temp!=NULL && temp->data != item_to_be_deleted){
		prev = temp;
		temp = temp->next;
	}

	if(temp == NULL)
		return;

	prev->next = temp->next;
	free(temp);
	
	
}
void printSLList(struct Linked *singLL){
	struct listNode *temp = singLL->head;
	if(isEmpty(singLL)){
		return;
	}
	while(temp!= NULL){
		printf("%d",temp->data);
		temp = temp->next;
		if(temp!=NULL)
			printf("\n");
	}

}
int main(){

	struct Linked *singLL;

	singLL = createList();

	insertInSinglyLinked(singLL, 5);

	insertInSinglyLinked(singLL, 2);

	insertInSinglyLinked(singLL, 12);

	insertInSinglyLinked(singLL, 10);

	printf("\nElements in List: %d\n", singlyListLength(singLL));
	
	printSLList(singLL);

	//deleting head node
	deleteNodeFromLinked(singLL, 10);

	printf("\nElements in List: %d\n", singlyListLength(singLL));

	printSLList(singLL);

	//deleting a node in list
	deleteNodeFromLinked(singLL, 2);

	printf("\nElements in List: %d\n", singlyListLength(singLL));

	printSLList(singLL);

	//inserting after deleting a node from the list
	insertInSinglyLinked(singLL, 7);

	printf("\nElements in List: %d\n", singlyListLength(singLL));

	printSLList(singLL);
	
	return 0;
}