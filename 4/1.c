#include<stdio.h>
#include<stdlib.h>
/*const number*/
#define INF  2147483647

/*ALU function*/

#define MAX(x,y) x > y ? x : y

/*graph*/
typedef struct 
{
	int v;
	int price;
	struct node* next;

}node;

typedef struct 
{
	node * first;
	node * last;
	int num;
	int acc_p;

}graph;

graph * head;
graph * parents;

void insert_graph(graph * head, int u, int v, int p);
/*Topology*/
//int * tpl;
int tpl[100000];
int * visited;
void topology(int V,int current);

/*stack*/
node * stack = NULL;
int stack_num = 0;
void push(int v);


int execute(int V, int E);


int main() 
{
	int t = 0;

	scanf("%d",&t);

	for (int i = 0; i < t; i++) {
		int V, E;
		//printf("/********** case %d ****************/\n", i);
		scanf("%d %d",&V,&E);
		head = (graph*)calloc(V, sizeof(graph));            /* graph DS*/
		parents = (graph*)calloc(V, sizeof(graph));         /* back tracking DS*/
		for (int i = 0; i < 100000; i++)
			tpl[i] = 0;										/*Topology DS*/
		  
		
		for (int j = 0; j < E; j++) {
			int u, v, p;

			scanf("%d %d %d",&u,&v,&p);                     /* input departure and dest ,and price*/
				
			insert_graph(head,u,v,p);                       /* insert the graph*/
			insert_graph(parents,v,u,p);                    /* insert  the backtracking graph*/
			
		}
		
		int result = execute(V,E);
		printf("%d\n",result);
		//printf("/********** case %d ****************/\n", i);
		

	}
	
	return 0;
}

void insert_graph(graph * head, int u, int v, int p)
{
	node * temp = (node*)malloc(sizeof(node));
	temp->next = NULL;
	temp->price = p;
	temp->v = v;
	

	if (head[u].first == NULL) {
		head[u].first = temp;
		head[u].last = temp;
	}
	else { // head[u].first is not empty
		head[u].last->next = temp;
		head[u].last = temp;
	}
	head[u].num++;
	return;
}

int execute(int V, int E) 
{

	visited = (int*)calloc(V, sizeof(int));     /*For topology sort, visited array*/
	
	topology(V,0);   /* do sort tht graph to linear*/
	free(visited);
	int index = 0;	 /*To save stack to array, index*/
	for (node * temp = stack; temp != NULL; temp = temp-> next) {
		//printf("stack %d : %d\n",index,temp->v);
		tpl[index] = temp->v;
		//printf("tpl[%d] : %d\n", index, tpl[index]);
		index++;
	}

	
	stack = NULL;


	/* DAG part*/
	int max = 0;

	head[0].acc_p = 0;      /*head point is zero*/

	for (int i = 1; i < V; i++) {
		int target = tpl[i];        /*tpl i'target index must be acc_p*/
		int temp_max = -1;
		for (node * temp = parents[target].first; temp != NULL; temp = temp->next) {
			int now_max = head[temp->v].acc_p + temp->price;
			if (head[temp->v].acc_p == -1)
				temp_max = -1;
			else if (temp_max < now_max)
				temp_max = now_max;
			
		}

		//printf("%d 's max = %d\n", target, temp_max);
				
		head[target].acc_p = temp_max;
		if (target == V - 1)
			return temp_max;
	}

	return -1;

}

void topology(int V, int current) 
{

	if (visited[current] == 1) return;
		
	visited[current] = 1 ;

	for (node * temp = head[current].first; temp != NULL; temp = temp->next) {
		int child = temp->v;
		topology(V,child);
	}
	
	push(current);
}

void push(int v) 
{
	node * temp = (node*)malloc(sizeof(node));
	temp->next = NULL;
	temp->price = -1;
	temp->v = v;
	if (NULL == stack){
		stack = temp;
	}
	else {
		temp->next = stack;
		stack = temp;
	}
	stack_num++;
	return;
}