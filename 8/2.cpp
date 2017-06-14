#include<iostream>

using namespace std;

struct node {
	int v;
	int c;
	node * next;
};

struct list{
	
	node*  head;
	int num;
	
	list() {
		head = NULL;
		num = 0;
	}

	void insertNode(int v, int c) {
		node * newNode = new node;

		newNode->v = v;
		newNode->c = c;
		
		if (head == NULL){
			newNode->next = NULL;
		}
		else {
			newNode->next = head;
		}

		head = newNode;
		num++;
	
	}

	bool findNode(int v) 
	{
		for (node * temp = head; temp != NULL; temp = temp->next) {
			if (temp->v == v)
				return true;
		}
	
		return false;
	}



};


char* execute(list * graph, int n, int * sol);

int main() 
{
	int  t = 0;

	cin >> t;
	for (int i = 0; i < t; i++) {
		int n, m, L;
		cin >> n >> m >> L;

		list * graph = new list[n];

		for (int j = 0; j < m; j++){
			int u, v, c;

			cin >> u >> v >> c;

			graph[u].insertNode(v, c);
			graph[v].insertNode(u, c);
		
		}
		int * sol = new int[n];
		for (int j = 0; j < n; j++)
			cin >> sol[j];


		char* result = execute(graph,n, sol);
		cout << result << endl;
		delete sol;
	}

	return 0;
}
char* execute(list * graph, int n, int * sol) {

	for (int i = 0; i < n - 1; i++) {
		if (graph[sol[i]].findNode(sol[i+1]) == false) {
			return "NO";
		}
	}

	if (graph[sol[n - 1]].findNode(sol[0]) == false)
		return "NO";

	return "YES";
}