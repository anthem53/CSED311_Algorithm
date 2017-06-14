#include<stdio.h>
#include<stdlib.h>

/* constant number */
#define MAX_MONEY 1000000
#define MAX_V 100000
#define MAX_E 200000

/*graph DS*/
typedef struct {
	int value;
	int price;
	struct node * next;
		
}node;

typedef struct {

	node* first;
	node* last;
	node* num;

}head;

void insert_graph(int u, int v, int p);
int IsUpdate(int u, int v, int p);

head* graph;

/*for caluating sum price*/

/*Queue*/
typedef struct {
	int ver;
	int dep;
	struct qnode* next;
}qnode;
typedef struct {
	qnode* first;
	qnode* last;
	int num;
}queue;
int dequeue(queue * head);
void enqueue(queue* head, int news, int dep);

/* problem part*/
void execution(int E, int V, int k);
int BFS(int V, int mid, int k);


int main() 
{
	int t = 0; 

	scanf("%d",&t);

	for (int i = 0; i < t; i++) {

		graph = (head*)calloc(MAX_E, sizeof(head));

		int V, E, k;
		scanf("%d %d %d", &V, &E, &k);
	
		for (int j = 0; j < E; j++) {
			int u, v, p;

			scanf("%d %d %d",&u,&v,&p);
		
			insert_graph(u, v, p);  /*dest is E - 1 node, returning departure is awful to money and time */
		}

		if (V == 1) {
			printf("%d\n",graph[0].first->price + 1);
		}
		else
			execution(E, V, k);


	}/*test case loop*/


	return 0;
}

void insert_graph(int u, int v, int p) 
{
	node* temp = (node*)malloc(sizeof(node));

	if (IsUpdate(u, v, p))
		return;

	temp->next = NULL;
	temp->price = p;
	temp->value = v;

	if (0 == graph[u].num) {
		
		graph[u].first = temp;
		graph[u].last = temp;
	
	}
	else {

		graph[u].last->next = temp;
		graph[u].last = temp;

	}

	graph[u].num++;
	return;

}

int IsUpdate(int u, int v, int p) {

	for (node * temp = graph[u].first; temp != NULL; temp = temp->next) {
		if (temp->value == v) {
			if (temp->price > p)
				temp->price = p;
			return 1;
		}
	}
	return 0;

}
void execution(int E, int V, int k) 
{
	int result = -1, L = 0, M = MAX_MONEY;
	int mid, IsResult = 0;

	while (L < M) {
		mid = (L + M) / 2;
		result = BFS(V, mid, k);

		if (result >= 0) {
			IsResult = 1;
			M = mid;
		}
		
		else if (result == -1)
			L = mid + 1;
	}
	if (IsResult) {
		printf("%d\n", L);
	}
	else{
		printf("%d\n", -1);
	}

	return;
}

int BFS(int V, int mid, int k) 
{
	int i = 0, dep = 0;


	int* visited = (int *)calloc(sizeof(int), V);
	queue* heads = (queue*)malloc(sizeof(queue));
	
	heads->first = NULL;
	heads->last = NULL;
	heads->num = 0;
	for (i = 0; i < V; i++)
		visited[i] = 0;

	visited[0] = 1;
	enqueue(heads, 0, dep);

	while (1) {
		if (heads->num == 0)
			break;

		dep = heads->first->dep;           /* current node  depth*/
		int y2 = dequeue(heads);
			
		for (node* temp = graph[y2].first; temp != NULL; temp = temp->next) {
						 
			if (visited[temp->value] == 0 && temp->price < mid) {

				if (temp->value == V - 1) {    /* find the node */                
					return mid;
				}
				visited[temp->value] = 1;

				if (dep + 1 < k) {
					enqueue(heads, temp->value, dep + 1);  
				}
			}
		}
	}

	return -1;
}


void enqueue(queue* heads, int news, int dep)
{
	qnode * temp = (qnode*)malloc(sizeof(qnode));

	temp->ver = news;
	temp->dep = dep;
	temp->next = NULL;

	temp->next = NULL;
	if (heads->first == NULL) {
		heads->first = temp;
		heads->last = temp;
	}
	else
		heads->last->next = temp;
	heads->last = temp;

	heads->num++;
}

int dequeue(queue * heads)
{
	int result = heads->first->ver;
	qnode* temp = heads->first;


	if (heads->num == 1) {
		heads->first = NULL;
		heads->last = NULL;
	}
	else {
		heads->first = heads->first->next;
	}
	heads->num--;
	free(temp);
	return result;
}
