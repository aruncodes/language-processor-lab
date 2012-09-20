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
