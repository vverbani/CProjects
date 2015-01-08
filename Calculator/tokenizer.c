/********************************************************************************
 * tokenizer.c
 * 
 * Computer Science 3357a
 * Assignment 1
 *
 * Author: Valmir Verbani 
 * Student Number: 250695712
 * 
 * This is the tokenizer class that reads in the string first and checks 
 * the size of the string, if its appropriate or not. Checks to see that we are 
 * only dealing with the correct operators and only numbers. Also checks for
 * misplaced parenthesis. 
 *  
*******************************************************************************/


#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <syslog.h>
#include "stack.h"
#include "tokenizer.h" 

//deals with examples such as --5 only
/*
void changeNega(char token[])
{
	int i = 0;

	while(token[i] != '\0')
	{
		if(token[i] = '-')
		{	
			int before = i - 1;
			int next = i + 1;

			//if next token is a number 
			if((token[next] >= 48 && token[next] <= 57) && 
				(token[before] < 48 || token[before] > 57))
			{

				//not done 
			}
		}
	}
}
*/
//this only works for for its a double negative number
// it changes the first - to a + and the second to a space
//spaces are dealt with in the shunting algorithm 
void changeToPos(char *token)
{
	int i = 0;

	while(token[i] != '\0')
	{
		if(token[i] == '-')
		{ 
		  int check = i + 1;
		  if (token[check] == '-')
			{
				token[i] = '+';
				token[check] = ' ';
			}
		}
	i++;
	}
}
// this checks the validity of the string
// only operators and operands ( not . )
int validChars(char *token)
{
	int i = 0;
	while(token[i] != '\0')
	{
		if(    token[i] != 40 && token[i] != 41
 			&& token[i] != 42 && token[i] != 43 && token[i] != 45
			&& token[i] != 47 && token[i] != 48 && token[i] != 49
			&& token[i] != 50 && token[i] != 51 && token[i] != 52
			&& token[i] != 53 && token[i] != 54 && token[i] != 55
			&& token[i] != 56 && token[i] != 57 )
		{
			//deleted token[1] != ' '
			syslog(LOG_ERR, "Status: invalid-expr");
			//printf("invalid-expr");
			return 0;
		}
		i++;
	}
	return 1;
}
//this checks the number of parenthesis of the string
// if misplaced parenthesis count is encountered, an invalid-expr
//message is prompt
//this also checks whether the string has surpased 78 characters or not
int brackCount(char *token)
{
	int leftbracket = 0;
	int rightbracket = 0;
	int i = 0;

	while(token[i] != '\0')
	{
		if(token[i] == 40)
		{
			leftbracket++;
		}
		if(token[i] == 41)
		{
			rightbracket++;
			
		}
		if(i > 78)
		{
			syslog(LOG_ERR, "Status: max-length-exceeded");
			//printf("max-length-exceeded\n");
		}
		
		token[i++];
	}
	if(leftbracket != rightbracket)
		{
			syslog(LOG_ERR, "Status: mismatch");
			//printf("mismatch\n");
			return 0;
		}
	
	return 1;
}
