#include<iostream>
#include<queue>
using namespace std;


struct node {
	int v;
	int c;
	node * next;
};

class list {
public:

	int num;
	int dep;
	int parent;
	int mCost;
	node* first;
	node* last;
	node * pNode;
	bool removed;

	list() {
		num = 0;
		dep = 0;
		parent = 0;
		mCost = 10000;
		first = NULL;
		last = NULL;
		pNode = NULL;
		removed = false;
	}
	void adding_graph(int v, int c)
	{
		node* temp = new node;
		temp->next = NULL;
		temp->v = v;
		temp->c = c;
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

int execute(list * graph, int n, int m);
int BFS(list * graph, int n, int m);


int main()
{
	int t = 0;

	cin >> t;
	for (int i = 0; i < t; i++) {

		int n, m, l;
		cin >> n >> m >> l;
		int numNode = n + m + 2; 

		list* graph = new list[numNode];

		for (int j = 0; j < n; j++) {
			graph[0].adding_graph(j + 1, 1);
		}

		for (int j = 0; j < m; j++) {
			graph[j + n + 1].adding_graph(numNode - 1, 1);


		}
		

		for (int j = 0; j < l; j++) {
			int u, v;

			cin >> u >> v ;
			graph[u + 1].adding_graph(v + n + 1, 1);
			
				
		}

		int result = execute(graph, n, m);

		cout << result << endl;

		for (int j = 0; j < n + m + 2; j++) {
			node * next = graph[j].first;
			for (node* temp = graph[j].first; temp != NULL; temp = next) {
				next = temp->next;
				delete temp;
			}

		}
		delete[] graph;

	}

	return 0;
}
int execute(list * graph, int n, int m)
{
	int temp = 1, result = 0, numNode = n + m + 2;
	while (1) {
		temp = BFS(graph, n, m);

		if (temp < 0)
			break;

		int minC = graph[numNode - 1].mCost, i = numNode - 1;
		result += minC;
		while (i > 0) {
			int current = i;
			graph[i].pNode->c -= minC;
			i = graph[i].parent;

			graph[current].adding_graph(i,1);
			

		}

	}

	return result;
}


int BFS(list * graph, int n, int m)
{
	int numNode = n+m+2;
	
	queue<int> queues;
	bool* visited = new bool[numNode];

	for (int i = 0; i < numNode; i++)
		visited[i] = false;

	
	queues.push(0);
	visited[0] = true;
	
	while (!queues.empty()) {
		int target = queues.front();
		queues.pop();


		for (node * temp = graph[target].first; temp != NULL; temp = temp->next) {
			if (visited[temp->v] == false && temp->c > 0) {

				graph[temp->v].dep = graph[target].dep + 1;

				visited[temp->v] = true;
				graph[temp->v].parent = target;
				graph[temp->v].pNode = temp;
				graph[temp->v].mCost = graph[target].mCost < temp->c ? graph[target].mCost : temp->c;


				if (temp->v == numNode - 1) {
					return graph[temp->v].dep;
				}
				queues.push(temp->v);
			}
		}


	}

	return -1; /* no  */
}




/*
*     Bfs를 통해서 0에서 v - 1로 가는거 구하기
*		이때 부모노드를 기록, +  부모노드를 따라가는데 최소 capacity도 기록
*		t에서 s로 거슬러 올라가면서 capacity 업데이트 // 이때의 capacity 만큼 전체 flow 증가
*
*		반복하다가 BFS로 T를 못찾는 경우를 발생 시 스탑.
*		이때의 flow return
*
*/