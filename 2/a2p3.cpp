#include<iostream>
using namespace std;

#define divider 20170317

struct matrix {
	long long int u;
	long long int m;
	long long int l;
};

matrix fibonaci(int n, matrix start);
matrix matrix_multiple(matrix a, matrix b);

const matrix unit = { 1, 1, 0};
matrix start;

int main() 
{
	int t = 0;

	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		
		start = unit;

		int result;
		if (n >= 2) {
			matrix temp = fibonaci(n, start);
			result = temp.m;
		}	
		else
			result = n;

		cout << result<< endl;
	}	

	return 0;
}

matrix fibonaci(int n, matrix start) {
		
	if (n == 1) {
		matrix temp = unit;
		return temp;
	}

	if ((n & 1) == 0) {
		
		matrix temp = fibonaci(n / 2, start);
		return matrix_multiple(temp, temp);
	}
	else {
		matrix temp = fibonaci((n-1) / 2, start);
		return matrix_multiple(matrix_multiple(temp, temp),unit);

	}


}
matrix matrix_multiple(matrix a, matrix b) {
	matrix result;

	result.u = (((a.u % divider * b.u % divider) % divider) % divider + ((a.m % divider * b.m % divider) % divider) % divider) % divider;
	result.m = (((a.u % divider * b.m % divider) % divider) % divider + ((a.m % divider * b.l % divider) % divider) % divider) % divider;
	result.l = (((a.m % divider * b.m % divider) % divider) % divider + ((a.l % divider * b.l % divider) % divider) % divider) % divider;

	return result;
}