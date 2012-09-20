
/*
 * 'Non Deterministic Finite State Automata'
 * This file is part of 'Non Deterministic Finite State Automata'
 *
 * Copyright (C) 2012 - Arun Babu
 *
 * 'Non Deterministic Finite State Automata' is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * 'Non Deterministic Finite State Automata' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 'Non Deterministic Finite State Automata'. If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdio.h"
#include "stdlib.h"

int finalstates[10];
int t[25][25][25],ipend=0,f_states=0,last_state=0,flag=0;

char inputs[25],input[25];

void add_input(char ip)
{
	int i;
	
	for (i = 0; i <= ipend; i++)	
		if(inputs[i] == ip )
			break;
	
	if( i > ipend )
		inputs[ipend++]=ip;
}

int get_ip_pos(char ip)
{
	int i;
	for (i = 0; i <= ipend; i++)
	{
		if(inputs[i] == ip)
			return i;
	}
	return -1;
}
int isfinal(int s)
{
	int i;
	for (i = 0; i < f_states; i++)
	{
		if(finalstates[i] == s)
			return 1;
	}
	return 0;
}

void advance(int cur,int iptr) {

	int ip_pos = get_ip_pos(input[iptr]);
	int i;

	if( ip_pos == -1) {
		printf("Unknown input symbol..\n");
		return;
	}

	if( isfinal(cur) && input[iptr] == '\0') {
		// printf("Accepted..\n");	
		flag=1;	
		// printf(" --> Accepted state:'%d' \t ip '%c' \t iptr+1 : '%c' \n",cur,input[iptr],input[iptr+1]);
		return;
	}

	// printf("\nState: '%d' \t InputSym : '%c' \t ip_pos : %d\n",cur,input[iptr],ip_pos);
	for (i = 0; i < 25; ++i)
	{
		if( t[cur][ip_pos][i] == -1) {
			// printf(" no trans from '%d' for '%c'\n",cur,inputs[ip_pos]);
			break;
		}
		// printf(" --> hopping from state '%d' to '%d' with '%c' for '%c'\n",cur,t[cur][ip_pos][i],input[iptr],input[iptr+1]);
		advance(t[cur][ip_pos][i],iptr+1);
	}

}

void main()
{
	int i,j,k,cur=0;
	int state,trans=0;
	char ip;
	
	for (i = 0; i < 25; i++)	{
		for (j = 0; j < 25; j++)
			for (k = 0; k < 25; ++k)			
				t[i][j][k] = -1;
		inputs[i] = '\0';
	}
	
	printf("\nEnter transitions in the format 'state input transition'. Enter '-1 0 0' quit :\n");
	
	while(1) 
	{
		scanf("%d %c %d",&state,&ip,&trans);

		if(state == -1) break;
		
		add_input(ip);
		
		int ip_pos = get_ip_pos(ip);

		for(i = 0; i < 25; ++i)
			if ( t[state][ip_pos][i] == -1 ) {
				t[state][ip_pos][i] = trans;
				break;
			}
		
		if(state>last_state) last_state = state;
	}
	
	printf("\nEnter final states,enter -1 to end :\n");
	
	while(1)
	{
		scanf("%d", &state);
		
		if( state == -1) break;
		finalstates[f_states++] = state;
		if(state> last_state) last_state=state;
	}
	
	/*printf("\nTable\n");
	for (k = 0; k < 2; ++k) {
		printf("Depth : %d\n",k+1);
		for (i = 0; i <= last_state; i++)
		{
			for (j = 0; j < ipend; j++)
				printf("%2d ",t[i][j][k]);
			printf("\n");
		}
	}*/
	printf("\nFinal states :");
	for (i = 0; i < f_states; i++)
			printf("%d ",finalstates[i]);
	printf("\nInput symbols : %s\n",inputs);
	
	while(1)
	{
		printf("\nEnter input string: ");
		// gets(input);//,25,stdin);
		scanf("%s",input);
		
		flag=0;
		advance(0,0);
		
		// if(!flag)
		// 	printf("Rejected\n");

		printf("%s\n", flag?"Accepted":"Rejected");
	}
}

