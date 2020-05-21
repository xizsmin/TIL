#include <stdio.h>

#define N_MAX			9	
#define MAX(x, y)		( (x) > (y) ? (x) : (y) )
int cost[N_MAX];
int N;
int target;

int ans = -1;

void f(int x, int cnt)
{
	if (x == 0) {
		ans = MAX(ans, cnt);
		return;
	}
	for(int i=0; i<N; ++i) {
		if (x < cost[i]) continue;
		f(x-cost[i], cnt+1);
	}
}

int g(int x)
{
	if (x == 0) return 0;
	int ret = -1;
	for(int i=0; i<N; ++i) {
		if (x < cost[i]) continue;
		ret = MAX(ret, g(x-cost[i])+1);
	}
	return ret;


}

int main(int argc, char **argv)
{
	scanf("%d", &N);
	scanf("%d", &target);
	for(int n=0; n<N; ++n) scanf("%d", cost+n);
//	f(target, 0);
//	printf("ans: %d\n", ans);
	printf("%d\n", g(target));
	return 0;
}

