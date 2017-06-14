#include<iostream>
using namespace std;

int student[1000][1000];
int student_num[1000];

int invitee(int n, int k);
void delete_invitee(int index, int n);
int main() 
{
	int t = 0;
	
	//scanf("%d",&t);
	cin >> t;
	for (int i = 0; i < t; i++) {
		int k, n;
		//scanf("%d %d",&n, &k);
		cin >> n >> k;
		for (int j = 0; j < n; j++) {
			int temp_num = 0;
			for (int k = 0; k < n; k++) {
				int temp_mark = 0;
				//scanf("%d",&temp_mark );
				cin >> temp_mark;
				student[j][k] = temp_mark;				
				if (temp_mark == 1)
					temp_num++;
			}
			student_num[j] = temp_num;

		} 
		int result = invitee(n,k);
		//printf("%d\n",result);
		cout << result << endl;

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
		decrease = 0;
		for (int index = 0; index < n; index++) {

			int temp_num = student_num[index];
			if ((temp_num < k || temp_num > now_n - k) && temp_num != -1) {
				delete_invitee(index,n);
								
				decrease++;
				result--;
				now_n--;
				if (result == 0)
					return result;
			}

		}
		 
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