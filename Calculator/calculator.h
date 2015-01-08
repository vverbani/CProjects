/********************************************************************************
 * calculator.h
 * 
 * Computer Science 3357a
 * Assignment 1
 *
 * Author: Valmir Verbani 
 * Student Number: 250695712
 *
 * This is the header file that defines all the methods from calculator.c and
 * allows me to use the methods in a different .c file.   
*******************************************************************************/


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define MAX 256

int evaluateToInfix(char *str);
int evaluatePostfix(char *output);
int precedence(char o1, char o2);

#endif