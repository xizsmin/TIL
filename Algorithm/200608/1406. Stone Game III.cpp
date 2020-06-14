//TBD: Loop-dp

#include <stdio.h>

#define N_MAX				50000
#define abs(x)				( (x) > (0) ? (x) : ((x)*(-1)) )
#define MIN(x, y)			( (x) > (y) ? (y) : (x) )
#define MAX(x, y)			( (x) < (y) ? (y) : (x) )

int arr[N_MAX];
int dp[N_MAX+3][2];
int N;

int ans = 1000000;

void f(int idx, int jdx, int turn, int val)
{
	if (idx >= N || jdx >= N) {
		printf("val: %d\n", val);
		ans = MIN(ans, abs(val));
		return;
	}
	// alice
	if (turn == 0) { 
			f(idx, jdx+1, 1, val+arr[idx]);

			f(idx, jdx+2, 1, val+arr[idx]+arr[idx+1]);

			f(idx, jdx+3, 1, val+arr[idx]+arr[idx+1] + arr[idx+2]);
	} else {

			f(idx+1, jdx, 0, val-arr[jdx]);

			f(idx+2, jdx, 0, val-arr[jdx]-arr[jdx+1]);

			f(idx+3, jdx, 0, val-arr[jdx]-arr[jdx+1] - arr[jdx+2]);
	}
	ans = MIN(ans, abs(val));

}

int g(int idx, int turn, int lev)
{
	if (idx >= N) return 0;
	int &ret = dp[idx][turn];
	if (ret) return ret;
	ret = 0;

	if (turn == 0) {
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Alice takes %d\n", arr[idx]);
		int tmp = (-1)*g(idx+1, 1, lev+1)+arr[idx];
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Alice->tmp:%d\n", tmp);

		for(int i=0; i<lev; ++i) printf(" ");
		printf("Alice takes %d, %d\n", arr[idx], arr[idx+1]);
		int tmp2 = (-1)*g(idx+2, 1, lev+1)+arr[idx]+arr[idx+1];
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Alice->tmp2:%d\n", tmp2);

		for(int i=0; i<lev; ++i) printf(" ");
		printf("Alice takes %d, %d, %d\n", arr[idx], arr[idx+1], arr[idx+2]);
		int tmp3 = (-1)*g(idx+3, 1, lev+1)+arr[idx]+arr[idx+1]+arr[idx+2];
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Alice->tmp3:%d\n", tmp3);

		ret = MAX(tmp, tmp2);
		ret = MAX(ret, tmp3);


	} else {
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Bob takes %d\n", arr[idx]);
		int tmp = (-1)*g(idx+1, 0, lev+1)+arr[idx];
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Bob->tmp:%d\n", tmp);

		for(int i=0; i<lev; ++i) printf(" ");
		printf("Bob takes %d, %d\n", arr[idx], arr[idx+1]);
		int tmp2 = (-1)*g(idx+2, 0, lev+1)+arr[idx]+arr[idx+1];
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Bob->tmp2:%d\n", tmp2);

		for(int i=0; i<lev; ++i) printf(" ");
		printf("Bob takes %d, %d, %d\n", arr[idx], arr[idx+1], arr[idx+2]);
		int tmp3 = (-1)*g(idx+3, 0, lev+1)+arr[idx]+arr[idx+1]+arr[idx+2];
		for(int i=0; i<lev; ++i) printf(" ");
		printf("Bob->tmp3:%d\n", tmp3);

		ret = MAX(tmp, tmp2);
		ret = MAX(ret, tmp3);

	}
	return ret;

}

int main(int argc, char **argv)
{
	scanf("%d", &N);
	for(int n=0; n<N; ++n) scanf("%d", arr+n);
//	f(0, 0, 0, 0);
//	for(int i=0; i<N_MAX+3; ++i) \
		dp[i][0] = -50000000, dp[i][1] = -50000000;
	printf("%d\n", g(0,0, 0));
	return 0;
}

