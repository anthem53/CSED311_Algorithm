#include<iostream>
using namespace std;

int main() 
{
	int t = 0;
	cin >> t;


	for (int i = 0; i < t; i++) {
	
		int n, m;
		cin >> n >> m;
		cout << n - 1 + (m - 1) * n << endl;
	
	}
	return 0;
}