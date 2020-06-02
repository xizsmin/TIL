#include <stdio.h>
#include <stdlib.h>

#define N_MAX			2000
#define M_MAX			2000

#define MIN(x, y)			( (x) < (y) ? (x) : (y) )
#define MAX(x, y)			( (x) > (y) ? (x) : (y) )

int arr1[N_MAX];
int arr2[M_MAX];
int N, M;
int ans = 20000;
int F;

int compare(const void *first, const void *second)
{
	if(*(int *)first > *(int *)second) return 1;
	else if(*(int *)first < *(int *)second) return -1;
	else return 0;
}

int check_arr1_inc(int start, int end)
{
	for(int i=start; i<=end; ++i) {
		if (arr1[i] <= arr1[i-1]) return 0;
	}
	return 1;
}

void f(int i, int j, int prev, int cnt, int lev)
{
	if (N > M) {
		if (j > M) {
			if(check_arr1_inc(i, N-1)) {
				for(int l=0; l<lev; ++l) printf(" ");
				printf("<%d> ", prev);
				for(int l=i; l<N; ++l) printf("<%d> ", arr1[l]);
				printf("\n");
				for(int l=0; l<lev; ++l) printf(" ");
				printf("[%d]count: %d\n", lev,cnt);
			}
			printf("[%d]count: %d\n", lev,cnt);
			ans = MIN(ans, cnt);
			return;
		}
		if (i > N) {
			for(int l=0; l<lev; ++l) printf(" ");
			printf("[%d]count: %d\n", lev, cnt);
			ans = MIN(ans, cnt);
			return;
		}
	}

//	for(int l=0; l<lev; ++l) printf(" ");
//	printf("[%d]f(%d, %d)->%d(%d)\n", lev, i, j, prev, cnt);

	if (/*arr1[i-1]*/prev < arr2[j]) {
		if (arr1[i] == arr2[j]) {
			for(int l=0; l<lev; ++l) printf(" ");
			printf("(a)%d->%d\n", prev, arr1[i]);
			f(i+1, j+1, arr1[i], cnt, lev+1);
		}
		else {
			for(int l=0; l<lev; ++l) printf(" ");
			printf("(b)%d->%d\n", prev, arr2[j]);
			f(i+1, j+1, arr2[j], cnt+1, lev+1);

			if(prev < arr1[i]) {
				for(int l=0; l<lev; ++l) printf(" ");
				printf("(c)%d->%d\n", prev, arr1[i]);
				f(i+1, j, arr1[i], cnt, lev+1);
			}
		}
	}
	else if (prev<arr1[i]){
		for(int l=0; l<lev; ++l) printf(" ");
		printf("(d)%d->%d\n", prev, arr1[i]);
		f(i+1, j+1, arr1[i], cnt, lev+1);
	}
	else {
		if (lev == MAX(N, M)) {
			printf("COUNT:%d\n", cnt);
			ans = MIN(ans, cnt);
			return;
		}
	}
}
int __f(int i, int j, int prev, int cnt, int lev)
{

	if (i == N) {
//		ans = MIN(ans, cnt);
		return 1;
	} else if (j == M){
		if (i< N && arr1[i] <= prev) {
			return N_MAX;
		}
		for(int k=i+1; k<N; ++k) {
			if (arr1[k] <= arr1[k-1]) {
				return N_MAX;
			}
		}
		//ans = MIN(ans, cnt);
		return 1;
	}



	for(int l=0; l<lev; ++l) printf(" ");
	printf("[%d] %d(%d)\n", lev, prev, cnt);
	int &ret = dp[i][j];
	for(int l=0; l<lev; ++l) printf(" ");
	printf("dp[%d][%d] = %d\n", i, j, ret);

	if (ret<2000) return ret;

	ret =2000;
	int tmp = 0;
	int tmp1 = 0;
	int tmp2 = 0;
	if (prev < arr2[j]) {
		tmp += __f(i+1, j+1, arr2[j], cnt+1, lev+1);
//		if (tmp < 2000) ret = tmp;
		ret = MIN(ret, tmp);
	}

	if (prev < arr1[i]) {
		tmp1 += __f(i+1, j, arr1[i], cnt, lev+1);
		tmp2 += __f(i+1, j+1, arr1[i], cnt, lev+1);
		tmp = MIN(tmp1, tmp2);
		ret = MIN(ret, tmp);
	}

	int tmp3 = 0;
	tmp3 += __f(i, j+1, prev, cnt, lev+1);
	ret = MIN(ret, tmp3);
	return ret;
}

int main(int argc, char **argv)
{
	scanf("%d", &N);
	scanf("%d", &M);
	F = MIN(N, M);
	for(int n=0; n<N; ++n) scanf("%d", arr1+n);
	for(int m=0; m<M; ++m) scanf("%d", arr2+m);
	qsort(arr2, M, sizeof(int), compare);
	for(int m=0; m<M; ++m) printf("%d", arr2[m]);
	printf("\n");


	f(0, 0, 0, 0, 0);
	printf("ans: %d\n", ans);

	return 0;
}
