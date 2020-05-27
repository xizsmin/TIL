#include <stdio.h>

#define N_MAX			2000
#define M_MAX			2000

#define MIN(x, y)			( (x) < (y) ? (x) : (y) )

int arr1[N_MAX];
int arr2[M_MAX];
int N, M;
int ans = 20000;

void f(int i, int j, int prev, int cnt, int lev)
{
	if (i == N || j == M) {
		ans = MIN(ans, cnt);
		return;
	}
	for(int l=0; l<lev; ++l) printf("-");
	printf("%d (%d, %d)", prev, i, j);

	if (arr2[j] > arr1[i-1]) {
		for(int l=0; l<lev; ++l) printf("-");
		printf("arr1[%d] <--> arr2[%d] can be swapped\n", i-1, j);

		f(i+1, j+1, arr2[j], cnt+1, lev+1);
		if (arr2[j] <= arr1[i])
			f(i+1, j+1, arr1[i], cnt, lev+1);
		else f(i+1, j, arr1[i], cnt, lev+1);
	} else {
		for(int l=0; l<lev; ++l) printf("-");
		printf("no swap will happen\n");
		if (arr2[j] <= arr1[i])
			f(i+1, j+1, arr1[i], cnt, lev+1);
		else f(i+1, j, arr1[i], cnt, lev+1);
	}
}

int main(int argc, char **argv)
{
	scanf("%d", &N);
	scanf("%d", &M);
	for(int n=0; n<N; ++n) scanf("%d", arr1+n);
	for(int m=0; m<M; ++m) scanf("%d", arr2+m);


	f(1,0,arr1[0],0, 1);

	f(1,1,arr2[0],1, 1);

	return 0;
}

