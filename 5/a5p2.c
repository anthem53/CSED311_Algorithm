#include<stdio.h>
#include<stdlib.h>

#define MIN(x,y) ((x < y) ? (x) : (y)) 
#define INT_MAXS 2147483647
typedef struct 
{
	int d;
	int p;
}city;

long long int fuel(city* node, int n, int D);

int main() 
{
	int t = 0;

	scanf("%d",&t);

	for (int i = 0; i < t; i++) {
		int D, n;

		scanf("%d %d",&D,&n);

		city * node = (city *)calloc(n, sizeof(city));
		
		for (int j = 0; j < n; j++) 
			scanf("%d %d",&node[j].d,&node[j].p);
		
		long long int result = fuel(node, n, D);

		printf("%lld\n",result);
	
	}

	return 0;
}
long long int fuel(city* node, int n, int D) 
{
	long long int result = 0;
	int least_p = INT_MAXS;
	for (int i = 0; i < n; i++) {
		int temp_d;

		least_p = MIN(least_p, node[i].p);

		if (i == n - 1)
			temp_d = D - node[i].d;
		else 
			temp_d = node[i + 1].d - node[i].d;

		result += temp_d* least_p;
	}

	return result;
}