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

	list() {
		num = 0;
		dep = 0;
		parent = 0;
		mCost = 10000;
		first = NULL;
		last = NULL;
		pNode = NULL;
	}
	void adding_graph(int v,int c)
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
		
		int n, m;
		cin >> n >> m;


		list* graph = new list[n];

		for (int j = 0; j < m; j++) {
			int u, v, c;

			cin >> u >> v >> c;
			graph[u].adding_graph(v, c);

		}

		int result = execute(graph,n,m);

		cout << result << endl;
	}

	return 0;
}
int execute(list * graph, int n, int m) 
{
	int temp= 1, result = 0;
	while (1) {
		 temp = BFS(graph, n, m);

		 if (temp < 0)
			 break;

		 int minC = graph[n - 1].mCost, i = n-1;
		 result += minC;
		 while(i > 0) {
			 
			 graph[i].pNode->c -= minC;
			 i = graph[i].parent;
			 
		 }

	} 

	return result;
}


int BFS(list * graph, int n, int m) 
{
	int minC = 10000;
	if (n == 1) {
		return 0;
	}
	queue<int> queues;
	bool* visited = new bool[n];

	for (int i = 0; i < n; i++)
		visited[i] = false;


	queues.push(0);
	visited[0] = true;

	int dep = 0;

	while (!queues.empty()) {
		int target = queues.front();
		queues.pop();


		for (node * temp = graph[target].first; temp != NULL; temp = temp->next) {
			if (visited[temp->v] == false && temp->c > 0 ) {

				graph[temp->v].dep = graph[target].dep + 1;
				
				visited[temp->v] = true;
				graph[temp->v].parent = target;
				graph[temp->v].pNode = temp;
				graph[temp->v].mCost = graph[target].mCost < temp->c ? graph[target].mCost : temp->c;

				
				if (temp->v == n - 1) {
					return graph[temp->v].dep;
				}
				queues.push(temp->v);
			}
		}


	}

	return -1; /* no  */
}




/*
 *     Bfs�� ���ؼ� 0���� v - 1�� ���°� ���ϱ�     
 *		�̶� �θ��带 ���, +  �θ��带 ���󰡴µ� �ּ� capacity�� ���
 *		t���� s�� �Ž��� �ö󰡸鼭 capacity ������Ʈ // �̶��� capacity ��ŭ ��ü flow ����
 *
 *		�ݺ��ϴٰ� BFS�� T�� ��ã�� ��츦 �߻� �� ��ž. 
 *		�̶��� flow return 
 *
 */