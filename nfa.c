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

	for (i = 0; i < 25; ++i)
	{
		if( t[cur][ip_pos][i] == -1)
			break;
		advance(t[cur][ip_pos][i],iptr+1);
	}

	if( isfinal(cur) && input[iptr+1] == '\0') {
		printf("Accepted..\n");	

		flag=1;	
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
	for (i = 0; i < last_state; i++)
	{
		for (j = 0; j < ipend; j++)
			printf("%2d ",t[i][j]);
		printf("\n");
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
		
		advance(0,0);
		
		if(!flag)
			printf("Rejected\n");
		flag=0;
	}
}

