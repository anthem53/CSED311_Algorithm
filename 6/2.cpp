#include<iostream>
using namespace std;

int main() 
{
	int t;

	cin >> t;

	for (int i = 0; i < t; i++) {
		int a, b;
		cin >> a >> b; 
		if ((a % 4 == 0 && b % 4 != 0) || (a % 4 != 0 && b % 4 == 0))
			cout << 'A' << endl;
		else if( a % 4 == 0 &&  b % 4 == 0)
			cout << 'B' << endl;
		else {
			if (a % 4 == 1 && b % 4 == 1)
				cout << 'B' << endl;
			else if (a % 4 != 1 && b % 4 == 1 || a % 4 == 1 && b % 4 != 1) 
				cout << 'A' << endl;
			else {
				int aMovePathNum = a + 1 - (a / 4 + 1) * 2;
				int bMovePathNum = b + 1 - (b / 4 + 1) * 2;
				if ((aMovePathNum + bMovePathNum) & 1 == 1) 
					cout << 'A' << endl;
				else
					cout << 'B' << endl; 
			}
		}
	}

	return 0;
}