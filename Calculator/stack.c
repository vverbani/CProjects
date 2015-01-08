/********************************************************************************
 * stack.c
 * 
 * Computer Science 3357a
 * Assignment 1
 *
 * Author: Valmir Verbani 
 * Student Number: 250695712
 * 
 * This is my stack file. I have two stack structs. One is a stack for just the 
 * operators while the other stack is just for the operands. They both have the 
 * same functions. For example, they have display where it displays all its 
 * stack contents, push where an operator/ operand is pushed onto the stack, 
 * there is pop where it pops the top item of the stack, there is the sizeOf 
 * function where it returns the size of the actual stack.  
*******************************************************************************/



#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>

#define MAXSIZE 50
//stack = struct stackOperator t
typedef struct StacksOperator
{
	char stk[MAXSIZE];
	int top;

}StackOperator;

//Operand stack
typedef struct StacksOperand
{
	int stk[MAXSIZE];
	int top;
}StackOperand;
//this is the push method for the operator stack
//it takes is a char parameter to push onto the stack
//before pushing it checks if it reached its max size
void pushOperator(StackOperator *t, char topValue)
{

	if (t->top == (MAXSIZE - 1))
	{
		printf("Check stack size \n");
	}
	else
	{
		t->top++;
		t->stk[t->top] = topValue;
	}
}
//same push function but for the operand stack
void pushOperand(StackOperand *t, int topValue)
{

	if (t->top == (MAXSIZE - 1))
	{
		printf("Check stack size \n");
	}
	else
	{
		t->top++;
		t->stk[t->top] = topValue;
	}
}
// function checking whether the stack is empty
int isOperatorEmpty(StackOperator *t)
{
	//if empty then return 1 ; true
	if(t->top == -1 )
	{
		return 1;
	}
	else
	{
	return 0 ;
	}
}

int isOperandEmpty(StackOperand *t)
{
	
	if(t->top == -1 )
	{
		return 1;
	}
	else
	{
	return 0 ;
	}
}
//pop function for the operator stack
//first checks if the stack is empty
//if not empty, it pops the top of the stack
//and returns the char value
char popOperator(StackOperator *t)
{
	
	char popedValue;

	if(t->top == -1)
	{
		printf("Can't pop, stackOperator is empty \n");
	}
	else 
	{
		popedValue = t->stk[t->top];
		t->top = t->top - 1;
	}

	return popedValue;

}
//pop function for the operand stack
//returns an integer value rather than the char
int popOperand(StackOperand *t)
{
	
	int popedValue;

	if(t->top == -1)
	{
		printf("Can't pop, StackOperand is empty \n");
	}
	else 
	{
		popedValue = t->stk[t->top];
		t->top = t->top - 1;
	}

	return popedValue;

}
//the displayOperator function displays all the
//contents of the operator staack
//it first checks if the stack is empty or not
void displayOperator(StackOperator *t)
{
	int i = 0;
	
	if(t->top == -1)
	{
		printf("Your stack operator is empty\n");
	}

	while(i <= t->top)
	{
	   printf("%c \n", t->stk[i]);
	   i++;
	}
}

void displayOperand(StackOperand *t)
{
	int i = 0;
	while(i <= t->top)
	{
	   printf("%c \n", t->stk[i]);
	   i++;
	   if(t->top == -1)
	   {
	   		printf("StackOperand is empty");
	   }
	}
}
//gets the size of the operator stack
int sizeOfOperator(StackOperator *t)
{
	return t->top;
}
//gets the size of the operand stack
int sizeOfOperand(StackOperand *t)
{
	return t->top;
	printf("size of top from size of operator %d \n", t->top);
}

