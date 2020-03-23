/*  Rebeka Henry
    10/25/2019
    RPN With Stacks
   
    Credits:

    The parsing of the character in the TestOperatorAndOperand function is credited to
    Devon Guinane
    Reverse Polish Notation in C
    Github source https://github.com/theDazzler/Reverse-Polish-Notation-in-C/blob/master/main.c
    1/20/2012

    Creating different functions for the operations, tracking
    the first operator, and popping items from the stack is credited to
    Dhaksha Koppad
    Office Hours
    10/24/2019

    Useful Conversion Strategies StackOverflow
    x = ch - '0';
    isdigit();

    Chris Young
    Convert Char Digit to Corresponding Integer in C
    StackOverflow
    https://stackoverflow.com/questions/628761/convert-a-character-digit-to-the-corresponding-integer-in-c
    03/10/2009
    

    Algorithm:

    1 2 3 * + =

    -start at first operator present in the stack (*) and since it is NOT (=) keep going
    -find the two values that are below the stack (3 2)
    -conduct the operation (3 * 2) = 6
    -remove the values (3 2) from the stack and insert new operand (6)

    -look for the next operator (+) and since it is NOT (=) keep going

    -this is the stack now (1 6)

    -find the two values that are below the stack (6 1)
    -conduct the operation (6 + 1) = 7
    -remove the values (6 1) from the stack and insert the new operand (7)

    look for the next operator (=) since it is (=) then STOP and display the value
    
    by this time, the stack will be empty since every element is popped from the stack
    until the operator

    keep prompting user until improper value is provided (~ p q etc)

    new functions

    add()
    sub()
    mult()
    divi()
    TestOperatorAndOperand() this will have the different operations and prompt the user-makes it easier to keep
    code in one spot
   
    existing functions to use

    isEmpty() to make sure that the stack is empty before prompting user again
    isFull() if the user enters values that are greater than the allotted capacity they specified
    push() to keep adding elements to the stack- the operators and operands. 
        -going to need to incorporate the checkOperator() function and checkOperand() here to make
        sure that the proper operators and operands are being used. If improper use, then terminate
        program
    pop() to access the next element in stack might need to pop the other element at the top
    createStack() because we need to have a stack for the program to work
*/



#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>


struct Stack {
    int top;
    int capacity;
    char *array;
};

struct Stack *createStack() {

    int capacity = 7;

    struct Stack *S = malloc(sizeof(struct Stack));
    if(!S) 
        return NULL;
    S->capacity = capacity;
    S->top = -1;
    S->array= malloc(S->capacity * sizeof(int));
    if(!S->array) 
        return NULL;
    return S;
}

//needed for the pop function to check whether the stack is empty
int isEmpty(struct Stack *S) {
    return (S->top == -1);  	// if the condition is true then 1 is returned else 0 is returned
}

/*don't need
int size(struct Stack *S) {
    return (S->top + 1);  
}*/

//need to check the status of the stack
int isFull(struct Stack *S){

    //if the condition is true then 1 is returned else 0 is returned
    return (S->top == S->capacity - 1); 
}
//stack size is fixed and is cleared every time so it should accommodate each operation
void doubleStack(struct Stack *S){

    S->capacity *= 2;
    S->array = realloc(S->array, S->capacity * sizeof(int));
}

//incorporate in the checkOperatorAndOperand function for the operations
void push(struct Stack *S, char data){
    if(isFull(S)) 
        doubleStack(S); 
    S->array[++S->top] = data;   
}

//incorporate for getting rid of values after each operation
int pop(struct Stack *S){
    /* S->top == - 1 indicates empty stack*/
    if(isEmpty(S)){	
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    else /* Removing element from  ‘top’ of the array and reducing ‘top’ by 1*/
        return (S->array[S->top--]); 
}

/*don't need
int peek(struct Stack *S){
    //S->top == - 1 indicates empty stack
    if(isEmpty(S)){	
        printf("\nStack is Empty\n");
        return INT_MIN;;
    }
    else 
        return (S->array[S->top]); 
}*/

/*don't really need since I am constantly getting rid of values in the stack after using them
void deleteStack(){
    struct Stack *S;
    if(S) {     
        if(S->array)  
             free(S->array);
                  free(S);
      }
}*/


/*Operations*/

int add(int x, int y){
    return x + y;
}

int sub(int x, int y){
    return x - y;
}

int mult(int x, int y){
    return x * y;
}

int divi(int x, int y){
    return x / y;
}


/*check if the operator or operand is at the top of the stack*/
void TestOperatorAndOperand(){
    char ch;

    struct Stack *stk = createStack();

    do{
        printf("Enter an RPN Expression: "); 
        while(1){

            scanf("%c", &ch);
            //exit statement if q is hit 
            if (ch == 'q'){
                break;
            }

            //get rid of white spaces
            if (ch != ' '){
                //because scanf reads in a newline
                if (ch == '\n'){
                    break;
                }

                //check if single digit
                if(isdigit(ch)){
                    //if the stack is not full convert to digit and push to the stack
                    if(!isFull(stk)){
                        push(stk, ch - '0');
                    }

                    else{
                        printf("Value is not a digit\n");
                        exit(-1);
                    }
                }

                //call the mult function
                if(ch == '*'){
                    push(stk, mult(pop(stk), pop(stk)));
                }

                //call the div function
                else if (ch == '/'){
                    push(stk, divi(pop(stk), pop(stk)));
                }

                //call the add function
                else if (ch == '+'){
                    push(stk, add(pop(stk), pop(stk)));
                }

                //call the subtract function
                else if (ch == '-'){
                    push(stk, sub(pop(stk), pop(stk)));
                }

                //display the overall value
                else if (ch == '='){
                    printf("Value of Expression: %d\n", pop(stk));
                      
                }
            }
        }
    }

    while(ch != 'q');
}