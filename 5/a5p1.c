#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct  {
	int parent;
	bool marked;
	
}node;



int perfect_matching(node* node_array, int num);

node * node_array;
int main() 
{
	int t = 0;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int num;
		scanf("%d",&num);

		node_array = (node *)calloc(num,sizeof(node));

		for (int j = 1; j < num ; j++) {
			int parent;
			scanf("%d",&parent);

			node_array[j].parent = parent - 1;
		}
		int result = perfect_matching(node_array, num);
		if (result == 1)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}

int perfect_matching(node* node_array, int num) 
{
	int result= 1;

	for (int i = num-1; i >= 0; i--) {
		int temp_parent = node_array[i].parent;
		if ((temp_parent != -1) && (node_array[i].marked == false)) {
			if (node_array[temp_parent].marked == false) {
				node_array[i].marked = true;
				node_array[temp_parent].marked = true;
			}
			else {
				return -1;
			}
		}
	}

	return result;
}
