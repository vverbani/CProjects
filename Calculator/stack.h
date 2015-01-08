/********************************************************************************
 * stack.h
 * 
 * Computer Science 3357a
 * Assignment 1
 *
 * Author: Valmir Verbani 
 * Student Number: 250695712
 *
 * This is the header file that defines all the methods from stack.c and
 * allows me to use the methods in a diffle .c file.   
*******************************************************************************/


#ifndef STACK_H_
#define STACK_H_

#define MAXSIZE (50)

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

void pushOperator(StackOperator *t, char topValue);
char popOperator(StackOperator *t);
int isOperatorEmpty(StackOperator *t);
void displayOperator(StackOperator *t);
int sizeOfOperator(StackOperator *t);

void pushOperand(StackOperand *t, int topValue);
int popOperand(StackOperand *t);
int isOperandEmpty(StackOperand *t);
void displayOperand(StackOperand *t);
int sizeOfOperand(StackOperand *t);

#endif