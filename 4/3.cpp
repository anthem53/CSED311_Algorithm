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
	int parent;
	head()
	{
		first = NULL;
		last = NULL;
		num = 0;
		acc_p = INT_MAXS;
		visited = 0;
		parent = 0;
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
		for (int i = 0; i < num; i++) {
			cout << temp->v << ' ';
			temp = temp->next;
		}
	}
	void clear() 
	{
		acc_p = INT_MAXS;
		visited = 0;
		parent = 0;
	}
};

head * graph;
/*P queue*/
struct CompareByFirst {
	constexpr bool operator()(pair<int, int> const & a,
		pair<int, int> const & b) const noexcept
	{
		return a.first > b.first;
	}
};

priority_queue<pair<int, int>, vector<pair< int, int >>, CompareByFirst>  minheap;  /*  */


int execution(int V, int E);



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

		int result = execution(V, E);

		cout << result << endl;

	}

	return 0;
}

int execution(int V, int E) 
{
	int min = INT_MAXS;

	for (int i = 0; i < V; i++) {
		//cout <<endl<<endl<< i << "th : " << endl<<endl;
		/*start node initializing*/
		graph[i].acc_p = 0;
		graph[i].visited = 0;
		/*other node initializing*/
		for (int j = 0; j < V; j++)
			if (j != i)
				graph[j].clear();


		minheap.push(make_pair(0, i));

		int rep = 0;
		while (0 == minheap.empty() && rep < V) {
			int acc_p = minheap.top().first;
			int current_v = minheap.top().second;

			minheap.pop();
			graph[current_v].visited = 1;
			//cout <<"from "<< current_v <<" :"<< graph[current_v].acc_p << endl;
			for (node * temp = graph[current_v].first; temp != NULL; temp = temp = temp->next) {
				if (graph[temp->v].visited == 0) {

					if (graph[temp->v].acc_p != INT_MAXS && graph[temp->v].parent != current_v) {
						int cycle_length = graph[temp->v].acc_p + graph[current_v].acc_p + temp->p;
						min = min < (cycle_length) ? min : cycle_length;
					}

					if (graph[temp->v].acc_p > graph[current_v].acc_p + temp->p) {
						graph[temp->v].acc_p = graph[current_v].acc_p + temp->p;
						graph[temp->v].parent = current_v;
					}

					//cout << "to " << temp-> v<<": " <<graph[temp->v].acc_p << endl;
					minheap.push(make_pair(graph[temp->v].acc_p, temp->v));
				}
			}

			rep++;
		}

		while (!minheap.empty())
			minheap.pop();
	}

	if (min== INT_MAXS)
		return -1;
	return min;
}