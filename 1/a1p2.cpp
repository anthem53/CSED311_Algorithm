#include<iostream>
using namespace std;

void quicksort(int * arr, int l,int r);
int partition(int* arr, int l, int r);

int main() 
{
	int t = 0;

	cin >> t;

	for (int i = 0; i < t; i++) {
		int n, * arr = NULL;

		cin >> n;
		arr = new int[n];

		for (int j = 0; j < n; j++) 
			cin >> arr[j];
		
		quicksort(arr, 0, n - 1);

		for (int j = 0; j < n; j++)
			cout << arr[j] << ' ';
		cout << endl;
	}

	return 0;
}

void quicksort(int * arr, int l, int r)
{
	int j = 0;
	if (l < r) {
		j = partition(arr, l, r);
		quicksort(arr, l, j-1);
		quicksort(arr, j + 1, r);
	}

}
int partition(int* arr, int l, int r)
{
	int pivot, L, R, for_swap;
	pivot = arr[l];
	L = l; 
	R = r+1;

	while (1) {
		do {
			L++;
		} while (arr[L] <= pivot && L <= R );
		do {
			R--;
		} while (arr[R] > pivot);

		if (L >= R)
			break;
		for_swap = arr[L]; arr[L] = arr[R]; arr[R] = for_swap;
	
	}
	for_swap = arr[l]; arr[l] = arr[R]; arr[R] = for_swap;

	return R;

}