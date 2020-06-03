// Calculating diagonal sum of each matrix
// Find number of rows/colums those have duplicated number(s)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int T;
int N;

#define N_MAX			100
int arr[N_MAX][N_MAX];
int ans[3]={0,};
int num[N_MAX+1];

void diagonal_sum()
{
	ans[0]=0 ; ans[1] = 0; ans[2] = 0;


	int col = 0;
	for(int n=0; n<N; ++n) {
		ans[0] += arr[n][col++];
		memset(num, 0, sizeof(num));
		for(int m=0; m<N; ++m) {
			if (num[arr[n][m]]) {
				ans[1]++; break;
			}
			num[arr[n][m]]++;
		}
	}
	for(int n=0; n<N; ++n) {
		memset(num, 0, sizeof(num));
		for(int m=0; m<N; ++m) {
			if (num[arr[m][n]]) {
				ans[2]++; break;
			}
			num[arr[m][n]]++;
		}

	}
}

int main(int argc, char **argv)
{
	int sum, row_dup, col_dup;
	scanf("%d", &T);
	for(int t=0; t<T; ++t) {
		scanf("%d", &N);
		for(int n=0; n<N; ++n) {
			for(int m=0; m<N; ++m) \
				scanf("%d", &arr[n][m]);
		}
		diagonal_sum();
		printf("Case #%d: %d %d %d\n", t+1, ans[0], ans[1], ans[2]);
	}
	return 0;
}

