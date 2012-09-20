#include "stdio.h"
#include "stdlib.h"
#include "string.h"


char input[100];
int ip=0;

void E(char begin[25],char end[25]);
void T(char begin[25],char end[25]);
void F(char*,char*);
void EPRIME(char*,char*);
void TPRIME(char*,char*);

void error() {
	printf("\nError..\n");
	exit(0);
}

void advance() {
	ip++;
}

void TPRIME(char *begin,char *end)
{
	//printf("T'\n");
	if (input[ip]=='*') {
		advance();
		F("","");
		TPRIME("","");
	}
}

void F(char *begin,char *end) 
{
	//printf("F\n");
	if(input[ip] == 'a' || input[ip] == 'b' || input[ip] == 'c') {
		advance();
	}
	else if (input[ip] == '(') {
		advance();
		E("","");
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

void T(char begin[25],char end[25]) 
{
	printf("%sFT'%s\t T->FT'\n",begin,end);
//	F("","");
	//TPRIME("","");
}

void EPRIME(char *begin,char *end) 
{
	//printf("E'\n");
	if (input[ip] == '+') {
		advance();
		T("","");
		EPRIME("","");
	}
}

void E(char begin[25],char end[25]) 
{
//	printf("E\n");
	printf("%sTE'%s\t E->TE'\n",begin,end);
	char beg[25]; 
	char endn[25];
	
	strcat(endn,"E'");
	strcat(endn,end);

	T(begin,endn);
	
	EPRIME("","");
}
	
int main ()
{
	printf("\nEnter input :");
	gets(input);	
	//printf("%s", input);
	E("E->"," ");
	
	if( ip == strlen(input) )
		printf("Success..\n");
	else
		printf("Error..\n");
	return 0;
}
