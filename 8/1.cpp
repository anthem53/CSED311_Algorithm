#include<iostream>
#include<algorithm>
#include<bitset>
#include <cstring>
using namespace std;

int excute(int dist[][12]);
int TSP(int dest,unsigned int set, int dist[][12]);

int n, m;

int main() 
{
	int t = 0;
	cin >> t;

	for (int i = 0; i < t; i++){

		int dist[12][12];

		cin >> n >> m;

		memset(dist, 0, sizeof(int) * 12 * 12);
		for (int j = 0; j < m; j++) {
			int u, v, c;
			cin >> u >> v >> c;
			dist[u][v] = c;
			dist[v][u] = c;
		}

		int result = excute(dist);

		cout << result << endl;

	}

	return 0;
}
int excute(int dist[][12]) 
{
	int result = 2147483647;
	bool resultChange = false;

	for (int i = 1; i < n; i++) {
		
		int temp = TSP(i, 0, dist);
		if (dist[0][i] > 0 && temp > 0) {
			result = min(result, temp + dist[0][i]);
			resultChange = true;
		}
	}
	if (resultChange == false)
		result = -1;


	return result;

}

int TSP(int dest, unsigned int set, int dist[][12])
{
	int mins = 2147483647;
	bool minsMarked = false;

	set = (1<< dest) | set;

	bitset<12> counts(set);

	if (counts.count() == n-1) {

		return dist[dest][0];
	}

	for (int i = 1; i < n; i++) {
		int index = 1 << i;
		if ((set & index) != index && dist[dest][i] > 0) {
			int temp = TSP(i, set, dist);
			if (temp > 0) {
				mins = min(mins, temp + dist[dest][i]);
				minsMarked = true;
			}				
			
		}
	}
	if (minsMarked == false)
		mins = -1;

	return mins;
}