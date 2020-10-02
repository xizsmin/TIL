
// https://leetcode.com/problems/count-all-possible-routes/
// TBD: dp

#include <stdio.h>
#define N_MAX			100
#define MOD_NUM			1000000007

#define abs(x)			( (x) > (0) ? (x) : ((-1)*(x)) )

int start = 0;
int finish = 2;
int fuel = 40;
int N = 3;
//int arr[100]={2,3,6,8,4};
//int arr[100]={4,3,1};
int arr[100] = {1,2,3};
int dp[100][201];

int f(int i, int x)
{

	if (dp[i][x] != -1) return dp[i][x];
	int &ret = dp[i][x];
	ret = 0;


	for(int j=0; j < N; ++j) {
		if (j == i) continue; 
		if (x < abs(arr[i]-arr[j])) continue;
		if (j == finish) {
			ret += (f(j, x-abs(arr[i]-arr[j])) + 1);
			ret %= MOD_NUM;
		} else {
			ret += f(j, x-abs(arr[i]-arr[j]));
			ret %= MOD_NUM;
		}
	}
	return ret;
}


int main(int argc, char **argv)
{
	for(int i=0; i<100; ++i) {
		for(int j=0; j<201; ++j) {
			dp[i][j] = -1;
		}
	}
	printf("%d\n", f(start, fuel));
	return 0;
}

