#include<stdio.h>
#include<stdlib.h>


int ** student;
int * student_num;

int invitee(int n, int k);
void delete_invitee(int index, int n);
void print_student(int n, int k);
void print_student_num(int n, int k);

int main() 
{
	int t = 0;
	
	scanf("%d",&t);

	for (int i = 0; i < t; i++) {
		int k, n;
		scanf("%d %d",&n, &k);

		student = (int**)calloc(n, sizeof(int *));
		student_num = (int *)calloc(n, sizeof(int));

		//for (int j = 0; j < n; j++)
	//		insert_node(j);                   /*insert 전용 만들기 */

		for (int j = 0; j < n; j++)
			student[j] = (int*)calloc(n, sizeof(int)); /*배열 만들기*/

		for (int j = 0; j < n; j++) {
			int temp_num = 0;
			for (int k = 0; k < n; k++) {
				int temp_mark = 0;
				scanf("%d",&temp_mark );

				student[j][k] = temp_mark;				
				if (temp_mark == 1)
					temp_num++;
			}
			student_num[j] = temp_num;

		} // 입력의 마지노선 
		// print_student( n,k);
		//print_student_num(n, k);
		int result = invitee(n,k);
		printf("%d\n",result);

		for (int j = 0; j < n; j++)
			free(student[j]);
		free(student);
		free(student_num);
	}
	return 0;
}
int invitee(int n, int k) 
{
	int result = n;
	int decrease = 0;
	int now_n = n - 1; /*비교해야할 학생들의 수*/
	do 
	{
		//int deleted_student = 0;
		decrease = 0;
		for (int index = 0; index < n; index++) {

			int temp_num = student_num[index];
			if ((temp_num < k || temp_num > now_n - k) && temp_num != -1) {
				delete_invitee(index,n);
				//print_student(n, k);
				//print_student_num(n, k);
				
				decrease++;
				result--;
				now_n--;
				//printf("나믄 n : %d\n", now_n);
				if (result == 0)
					return result;
			}

		}
		 
		//printf("decrease : %d\n", decrease);
		//printf("result : %d\n", result);
	} while (decrease > 0 );

	return result;
}

void delete_invitee(int index, int n)
{
	student_num[index] = -1;
	for (int i = 0; i < n; i++){
		student[index][i] = 0;

		if (student[i][index] == 1){
			student[i][index] = 0;
			student_num[i]--;
		}
	}
}

void print_student(int n, int k) 
{
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) 
			printf("%d ",student[i][j]);
		
		printf("\n");
	}

}
void print_student_num(int n, int k) 
{
	for (int i = 0; i < n; i++) {
		printf("%dth number : %d\n",i+1, student_num[i]);
		
	}
}

/* version 1
int invitee(int n, int k) 
{
	int result = 0;
	int decrease = 0;
	int remind = n;
	do {
		decrease = 0;

		for (node * temp = list.first; temp != NULL; temp = temp->next) {
			int index = temp->num;

			if (student_num[index] < k || student_num[index] > n - k) {
				delete_node(index);
				decrease++;
				delete_invitee(index);
				remind--;
			}

		}

	} while (decrease > 0);

	
	return remind;
}

void delete_invitee(int index) 
{
	for (node * temp = list.first; temp != NULL; temp = temp->next) {
		if (student[temp->num][index] == 1) {
			student[temp->num][index] = 0;
			student_num[temp->num]--;
		}
	}
}*/
/*
void insert_node(int n) {
	node * temp = (node*)malloc(sizeof(node));
	temp->prev = NULL;
	temp->next = NULL;
	temp->num = n;

	if (list.first == NULL) {
		list.first = temp;
		list.last = temp;
		
	}
	else { // list.first is not NULL
		list.last->next = temp;
		temp->prev = list.last;
		list.last = temp;
		
	}
	list.num++;

}

void delete_node(int n) {

	
	
	if (list.first->num == n) {
		list.first = list.first->next;
		return;
	}
	else if (list.last->num == n) {
		list.last = list.last->prev;
		return;
	}
	for (node * temp = list.first; temp->next != NULL; temp = temp->next) {
		if (temp->num == n) {
			node* prev = temp->prev;
			prev->next = temp->next;
			return;
		}
	}


}*/