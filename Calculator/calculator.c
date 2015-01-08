/********************************************************************************
 * calculator.c
 * 
 * Computer Science 3357a
 * Assignment 1
 *
 * Author: Valmir Verbani 
 * Student Number: 250695712
 * 
 * This is the main class where it puts the string into a postfix expression
 * It uses the Shunting yard algorithm. Once it is in a postfix expression
 * it calculates the actual integer.  
*******************************************************************************/

#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <syslog.h>

#include "stack.h"
//#include "queue.h"
#include "tokenizer.h"
#include "getopt.h"
#define MAX 256

int evaluatePostfix(char *output);
int precedence(char o1, char o2);

int main()
{
	openlog("caculator", LOG_PID | LOG_NDELAY , LOG_USER);

	char str[] = "5+5";
	// before handing this in, add the parser checks
	changeToPos(str);
	if(brackCount(str) == 1 && validChars(str) == 1){ 
  int i = evaluateToInfix(str);\
 //	syslog(LOG_INFO,"Status: ok");
 //	syslog(LOG_INFO, "Result: %d", i);
	printf("%d \n", i);
	}
	closelog();
}

int evaluateToInfix(char *str)
{ 
	int value;
	char output[MAX];
	StackOperator operator;
	operator.top = -1;

	int i = 0;
	int a = 0;
	int check = 0;
	
	//while there are characters in the array
	while(str[i] != '\0')
	{
		//if its a number/ output to array
		if((str[i] >= 48 && str[i] <= 57))
		{
			output[a] = str[i];
			a++;
		}
		//cases with space
		if(str[i] == ' ')
		{
			//pop operators 
			if(operator.stk[operator.top] != '(')
			{
				output[a] = popOperator(&operator);
				a++;
			}
		}
		//if its + , - , /, *
		if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')
		{
			//store the operator onto char o1
			char o1 = str[i];
			if(operator.stk[operator.top] == '+' || operator.stk[operator.top] == '-' ||
				operator.stk[operator.top] == '/' || operator.stk[operator.top] == '*')
				{
					//check precendence
					//whenever o1 is lower precedence than o2, 
					//pop o2 off stack, onto output
					char o2 = operator.stk[operator.top];
					if( precedence(o1,o2) == 1)
					{
						output[a] = popOperator(&operator);
						a++;
					}
				}
			pushOperator(&operator, o1);
		}
		//if its left parenthesis
		if(str[i] == '(')
		{
			pushOperator(&operator, str[i]);
		}
		//if its right parenthesis
		if(str[i] == ')')
		{
			if(operator.stk[operator.top] != '(')
			{
				output[a] = popOperator(&operator);
				a++;
			}
			char disregard;
			disregard = popOperator(&operator);
			
		}
		i++;
	}
	//if there are any operators still in the stack, pop them
	while(sizeOfOperator(&operator) != -1)
	{
		//pop the last operator onto the output array
		output[a] = popOperator(&operator);
		//increment a for the array
		a++;
	}
			//set the last position of the array to null
	output[a] = '\0';	
	value = evaluatePostfix(output);
}
int evaluatePostfix(char *output)
{
	StackOperand op2;
	op2.top = -1;

	int stack[MAX];
	int top = 0;
	int c = 0;

	//parses the postfix expression and returns it value
	while(output[c] != '\0')
	{
		//if its an operand 
		if((output[c] >= 48 && output[c] <= 57 ))
		{
			//printf("numbers going in are :%c \n",output[c]);

			stack[++top] =  output[c] - '0';
		}
		else{
			char a,b;
			int value;
			//when only the final value is on the stackS
			if(top < 2)
			{
				printf("Stack Empty!\n");
				exit(1);
			}
		
			b = stack[top--];
			a = stack[top--];

			//check to see which operator is next
			//then perform the task corresponding to the operator
			switch(output[c])
			{
				case '+':
					value = a + b;
					printf("value is %c \n", value);
					break;
				case '-':
					value = a - b;
					break;
				case '*':
					value = a * b;
					break;
				case '/':
					if(b = 0)
					{
						value = 0 ;	
					}
					value = a / b;
					break;
				default:
					break;
			}
		//'push' the final value onto the stack
		stack[++top] = value;
		}	
		c++;
	}
	//return the top of the stack ; our final value
	return stack[top];
}
//helper method that checkes that o1 is either less or equal precedence
//to o2, returns 1 if it is, 0 otherwise
int precedence(char o1, char o2)
{
	if(( o1 == '+' && o2 == '-' )||
	(o1 == '+' && o2 == '+') ||
	(o1 == '+' && o2 == '(') ||
	((o1 == '+' && (o2 == '*' || o2 == '/'))) ||
	(o1 == '-' && o2 == '(') ||
	((o1 == '-' && (o2 == '*' || o2 == '/'))) ||
	(o1 == '-' && o2 == '-') ||
	(o1 == '*' && o2 == '/')||
	((o1 == '/' && o2 == '*')) ||
	(o1 == '*' && o2 == '*') ||
	((o1 == '*' && o2 == '(') || o1 == '/' && o2 == '(') ||
	(o1 == '/' && o2 == '/') )
	{
		return 1;
	}
	else {
		return 0;
	}
}
