#include <stdio.h>

#define N_MAX			2000
#define M_MAX			2000

#define MIN(x, y)			( (x) < (y) ? (x) : (y) )
#define MAX(x, y)			( (x) > (y) ? (x) : (y) )

int arr1[N_MAX];
int arr2[M_MAX];
int N, M;
int ans = 20000;
int F;

int check_arr1_inc(int base, int offset)
{
	for(int i=base; i<base+offset; ++i) {
		if (arr1[i] <= arr1[i-1]) return 0;
	}
	return 1;
}

void f(int i, int j, int prev, int cnt, int lev)
{
	if (i == F) {
		if (M == F) ans = MIN(ans, cnt);
		else if (N == F) {
			/* check if the rest of arr1[] gets strictly increasing */
			return;
		}
		return;
	}
	for(int l=0; l<lev; ++l) printf(" ");
	printf("%d\n", prev);

	if (/*arr1[i-1]*/prev < arr2[j]) {
		if (arr1[i] == arr2[j]) f(i+1, j+1, arr1[i], cnt, lev+1);
		else {
			f(i+1, j+1, arr2[j], cnt+1, lev+1);
			f(i+1, j+1, arr1[i], cnt, lev+1);
		}
	}
	else {
		f(i+1, j+1, arr1[i], cnt, lev+1);
	}
}

int main(int argc, char **argv)
{
	scanf("%d", &N);
	scanf("%d", &M);
	K = MIN(N, M);
	for(int n=0; n<N; ++n) scanf("%d", arr1+n);
	for(int m=0; m<M; ++m) scanf("%d", arr2+m);


	f(0, 0, 0, 0, 0);

	return 0;
}
