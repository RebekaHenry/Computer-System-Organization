#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H

struct Stack *createStack();

int isEmpty(struct Stack *S);

int size(struct Stack *S);

int isFull(struct Stack *S);

void doubleStack(struct Stack *S);

void push(struct Stack *S, char data);

int pop(struct Stack *S);

int peek(struct Stack *S);

void deleteStack();

int add(int x, int y);

int sub(int x, int y);

int mult(int x, int y);

int divi(int x, int y);

void TestOperatorAndOperand();




#endif
 


