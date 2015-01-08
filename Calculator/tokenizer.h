/********************************************************************************
 * tokenizer.h
 * 
 * Computer Science 3357a
 * Assignment 1
 *
 * Author: Valmir Verbani 
 * Student Number: 250695712
 * 
 * This is the header file for the tokenizer class. It allows us to use 
 * the following methods (below) in our calculator.c file.
 *  
*******************************************************************************/


#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "stack.h"

#define OPERAND 0
#define OPERATOR 1

#define PLUS 0
#define MINUS 1
#define MULTIPLY 2
#define DIVIDE 3
#define POWER 4
#define MOD 5
#define RBRACKET 6
#define LBRACKET 7

int validChars(char token[]);
int brackCount(char token[]);
void changeToPos(char token[]);
void changeNega(char token[]);

#endif