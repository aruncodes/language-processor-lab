#include "stdio.h"

int finalstates[10];
int t[25][25],ipend=0,f_states=0,last_state=0;

char inputs[25];

void add_input(char ip)
{
	int i;
	
	for (i = 0; i <= ipend; i += 1)	
		if(inputs[i] == ip )
			break;
	
	if( i > ipend )
		inputs[ipend++]=ip;
}

int get_ip_pos(char ip)
{
	int i;
	for (i = 0; i <= ipend; i += 1)
	{
		if(inputs[i] == ip)
			return i;
	}
	return -1;
}
int isfinal(int s)
{
	int i;
	for (i = 0; i < f_states; i += 1)
	{
		if(finalstates[i] == s)
			return 1;
	}
	return 0;
}

void main()
{
	int i,j,cur=0,flag=0;
	int state,trans=0;
	char ip,input[25];
	
	for (i = 0; i < 25; i += 1)	{
		for (j = 0; j < 25; j += 1)
			t[i][j] = -1;
		inputs[i] = '\0';
	}
	
	printf("\nEnter transitions in the format 'state input transition'. Enter '-1 0 0' quit :\n");
	
	while(1) 
	{
		scanf("%d %c %d",&state,&ip,&trans);

		if(state == -1) break;
		
		add_input(ip);
		
		t[state][get_ip_pos(ip)] = trans;
		
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
	
	printf("\nTable\n");
	for (i = 0; i < last_state; i += 1)
	{
		for (j = 0; j < ipend; j += 1)
			printf("%2d ",t[i][j]);
		printf("\n");
	}
	printf("\nFinal states :");
	for (i = 0; i < f_states; i += 1)
			printf("%d ",finalstates[i]);
	printf("\nInput symbols : %s\n",inputs);
	
	while(1)
	{
		printf("\nEnter input string: ");
		// gets(input);//,25,stdin);
		scanf("%s",input);
		
		// printf("Input string is %s\n",input);
		for (i = 0; input[i] != '\0'; i += 1)
		{
			// printf("\n curent char : '%c' (%d) ",input[i],input[i]);
			if(get_ip_pos(input[i]) == -1){ 
				printf("%c not found in inputs\n",input[i]);
				break; 
			}
				
			cur = t[cur][get_ip_pos(input[i])];
			
			if(cur == -1) break;
			
			if(isfinal(cur) && input[i+1] == '\0')
			{
				printf("Accepted..\n");
				flag=1;
				break;
			}
		}
		if(flag == 0)
			printf("Rejected..\n");
			
		cur=0;
		flag=0;
	}
}

