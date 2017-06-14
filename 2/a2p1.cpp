#include<iostream>
using namespace std;
long long int fibonaci_modulo(unsigned int n, unsigned int k,int divider);

int main() 
{
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		unsigned int n, k;

		cin >> n >> k;
		int result = fibonaci_modulo(n, k, 20170317);

		cout << result << endl;
	}

	return 0;
}

long long int fibonaci_modulo(unsigned int n, unsigned int k, int divider)
{
	static int num =0;
	//cout << ++num << endl;
	if (k == 0)
		return 1;
	if (n <= 1)
		return n;
	if (k == 1)
		return n % divider;

	long long int result;
	if (k % 2 == 0) {  // divider is even
		long long int temp = (fibonaci_modulo(n, k / 2, divider) % divider);
		result = ( (temp % divider) * (temp % divider)) % divider;
	}
	else {// divider is odd
		long long int temp = fibonaci_modulo(n, (k - 1) / 2, divider);
		result = ((n % divider) *(temp % divider * temp % divider) % divider) % divider;
	}
	
	return result; 
}