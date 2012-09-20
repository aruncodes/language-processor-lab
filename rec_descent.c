/*
 * 'Recursive Descent Parsing'
 * This file is part of 'Recursive Descent Parsing'
 *
 * Copyright (C) 2012 - Arun Babu
 *
 * 'Recursive Descent Parsing' is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * 'Recursive Descent Parsing' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 'Recursive Descent Parsing'. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


char input[100];
int ip=0;

void E();
void T();
void F();
void EPRIME();
void TPRIME();

void error() {
	printf("\nError..\n");
	exit(0);
}

void advance() {
	ip++;
}

void TPRIME()
{
	//printf("T'\n");
	if (input[ip]=='*') {
		advance();
		F();
		TPRIME();
	}
}

void F() 
{
	//printf("F\n");
	if(input[ip] == 'a' || input[ip] == 'b' || input[ip] == 'c') {
		advance();
	}
	else if (input[ip] == '(') {
		advance();
		E();
		if( input[ip] == ')' ) {
			advance();
		}
		else {
			error();
		}
	}
	else {
		error();
	}
}

void T() 
{
	//printf("T\n");
	F();
	TPRIME();
}

void EPRIME() 
{
	//printf("E'\n");
	if (input[ip] == '+') {
		advance();
		T();
		EPRIME();
	}
}

void E() 
{
	//printf("E\n");
	T();
	EPRIME();
}
	
int main ()
{
	printf("\n\nEnter input :");
	gets(input);	
	//printf("%s", input);
	E();
	
	if( ip == strlen(input) )
		printf("Success..\n");
	else
		printf("Error..\n");
	return 0;
}
