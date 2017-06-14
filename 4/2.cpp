#include<iostream>
#include<queue>
using namespace std;

#define INT_MAXS  2147483647

struct node
{
	int v;
	int p;
	node * next;
};

class head 
{

public:
	

	node* first;
	node * last;
	int num;
	int acc_p;
	int visited;
	head()
	{
		first = NULL;
		last = NULL;
		num = 0;
		acc_p = INT_MAXS;
		visited = 0;
	}
	void insert_graph(int v, int p) 
	{
		node * temp = new node;
		temp->next = NULL;
		temp->p = p;
		temp->v = v;


		if (first == NULL) {
			first = temp;
			last = temp;
		}
		else { // head[u].first is not empty
			last->next = temp;
			last = temp;
		}
		num++;
		return;
	}
	void print() { 

		node* temp = first;
		for (int i = 0; i < num; i++){			
			cout<< temp->v <<' ';
			temp = temp->next;			
		}
	}
	
};

int execution(int V, int E);

head * graph;
void print_graph(int V);



struct CompareByFirst {
	constexpr bool operator()(pair<int, int> const & a,
		pair<int, int> const & b) const noexcept
	{
		return a.first > b.first;
	}
};

priority_queue<pair<int, int>,vector<pair< int, int >>, CompareByFirst>  minheap;  /*  */

int main() 
{
	int t = 0;

	cin >> t;

	for (int i = 0; i < t; i++) {
		int V, E;
		cin >> V >> E;
		
		graph = new head[V]; 
		for (int j = 0; j < E; j++) {
			int u, v, p;

			cin >> u >> v >> p;

			graph[u].insert_graph(v, p);
			graph[v].insert_graph(u, p);
			

		}
	
		int result = execution(V , E);
		/*
		for (int j = 0; j < V; j++) {
			cout << j << "th acc : " << graph[j].acc_p << endl;
		}
		*/
		cout << result << endl;

	}

	return 0;
}

int execution(int V ,int E)
{

	graph[0].acc_p = 0;
	minheap.push(make_pair(0,0));

	int rep = 0;
	while (0 == minheap.empty() && rep < V ) {
		int acc_p = minheap.top().first;
		int current_v = minheap.top().second;

		minheap.pop();
		graph[current_v].visited = 1;
		//cout <<"from "<< current_v <<" :"<< graph[current_v].acc_p << endl;
		for (node * temp = graph[current_v].first; temp != NULL; temp = temp = temp->next) {
			if (graph[temp->v].visited == 0) {
				if (graph[temp->v].acc_p > graph[current_v].acc_p + temp->p)
					graph[temp->v].acc_p = graph[current_v].acc_p + temp->p;

				//cout << "to " << temp-> v<<": " <<graph[temp->v].acc_p << endl;
				minheap.push(make_pair(graph[temp->v].acc_p, temp->v));
			}
		}
		
		rep++;
	}
	
	while (!minheap.empty())
		minheap.pop();
	

	if (graph[V - 1].acc_p == INT_MAXS)
		return -1;
	return graph[V-1].acc_p;
}

void print_graph(int V) 
{
	for (int i = 0; i < V; i++) {
		cout << i << "th : ";
		graph[i].print();
		cout << endl;
	}

}