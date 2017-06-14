#include<iostream>
#include<queue>

using namespace std;

struct node {
	int v;
	node * next;
};

class list {
public:
	
	int num;
	int dep;
	node* first;
	node* last;
		
	list() {
		num = 0;
		dep = 0;
		first = NULL;
		last = NULL;
	}
	void adding_graph(int v) 
	{
		node* temp = new node;
		temp->next = NULL;
		temp->v = v;

		if (first == NULL) {
			first = temp;
			last = temp;
		}
		else {
			last->next = temp;
			last = temp;
		}
		num++;
	}


};

void execution(list* graph, int V);

int main() 
{
	int t = 0;
	cin >> t; 
	for (int i = 0; i < t; i++) {
		int V, E;

		cin >> V >> E;
		list* graph = new list[V];

		for (int j = 0; j < E; j++) {
			int u, v;
			cin >> u >> v;
			graph[u].adding_graph(v);
		}
		execution(graph, V);
	
	}
	return 0;
}

void execution(list* graph, int V) 
{
	if (V == 1){
		cout << 0 << endl;;
		return;
	}
	queue<int> queues;
	bool* visited = new bool[V];

	for (int i = 0; i < V; i++)
		visited[i] = false;

	
	queues.push(0);
	visited[0] = true;

	int dep = 0;

	while (!queues.empty()) {
		int target = queues.front();
		queues.pop();
	
		
		for (node * temp = graph[target].first; temp != NULL; temp = temp->next) {
			if (visited[temp->v] == false) {

				graph[temp->v].dep = graph[target].dep + 1;
				if (temp->v == V-1) {
					cout << graph[temp->v].dep << endl;
					return;
				}
				
				visited[temp->v] = true;
				queues.push(temp->v);
			}
		}
		
		
	}

	cout << -1 << endl;
	return;
}