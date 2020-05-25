#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define H_MAX			15
#define W_MAX			15
#define MAX(x, y)		( (x) > (y) ? (x) : (y) )
#define MAGIC_NUM		200

int arr[H_MAX][W_MAX];
int visited[H_MAX][W_MAX];
int dp[H_MAX][W_MAX];
int H, W;

int ans = 0;

int out_of_bound(int y, int x)
{
	return (y == H || x == W || y <0 || x < 0) ;
}

void f(int y, int x, int sum, int lev)
{
	if (y == H || x == W || y <0 || x < 0) {
		ans = MAX(ans, sum);
		return;
	}
	visited[y][x] = 1;

	//ans = MAX(ans, sum+arr[y][x]);

	if (!visited[y+1][x] && arr[y+1][x] != MAGIC_NUM)
		f(y+1, x, sum + arr[y][x], lev+1);
	if (!visited[y-1][x] && arr[y-1][x] != MAGIC_NUM)
		f(y-1, x, sum + arr[y][x], lev+1);
	if (!visited[y][x+1] && arr[y][x+1] != MAGIC_NUM)
		f(y, x+1, sum + arr[y][x], lev+1);
	if (!visited[y][x-1] && arr[y][x-1] != MAGIC_NUM)
		f(y, x-1, sum + arr[y][x], lev+1);
	visited[y][x] = 0;
	ans = MAX(ans, sum+arr[y][x]);
}

int __f(int y, int x, int lev)
{
	if(out_of_bound(y, x)) return 0;
	//if (arr[y][x] == MAGIC_NUM) return 0;

	int &r= dp[y][x];
	if(r) return r;

	int ret = 0;
	int tmp = 0;
	visited[y][x] = 1;
	if (!visited[y+1][x] && arr[y+1][x] != MAGIC_NUM) {
		//for(int i=0; i<lev; ++i) printf(" ");
		//printf("(%d, %d)%d ----> (%d, %d)%d\n", y, x, arr[y][x], y+1, x, arr[y+1][x]);
		tmp = __f(y+1, x, lev+1);
		ret = MAX(ret, tmp);
	}

	if (!visited[y-1][x] && arr[y-1][x] != MAGIC_NUM) {
		//for(int i=0; i<lev; ++i) printf(" ");
		//printf("(%d, %d)%d ----> (%d, %d)%d\n", y, x, arr[y][x], y-1, x, arr[y-1][x]);
		tmp = __f(y-1, x, lev+1);
		ret = MAX(ret, tmp);
	}
	if (!visited[y][x+1] && arr[y][x+1] != MAGIC_NUM) {
		//for(int i=0; i<lev; ++i) printf(" ");
		//printf("(%d, %d)%d ----> (%d, %d)%d\n", y, x, arr[y][x], y, x+1, arr[y][x+1]);
		tmp = __f(y, x+1, lev+1);
		ret = MAX(ret, tmp);
	}
	if (!visited[y][x-1] && arr[y][x-1] != MAGIC_NUM) {
		//printf("(%d, %d)%d ----> (%d, %d)%d\n", y, x, arr[y][x], y, x-1, arr[y][x-1]);
		tmp = __f(y, x-1, lev+1);
		ret = MAX(ret, tmp);
	}
	visited[y][x] = 0;;

	return r = (ret+arr[y][x]);


}



int main(int argc, char **argv)
{
	scanf("%d", &H);
	scanf("%d", &W);
	for(int h=0; h<H; ++h) \
		for(int w=0; w<W; ++w)\
			scanf("%d", &arr[h][w]);
	for(int h=0; h<H; ++h) \
		memset(dp[h], -1, sizeof(dp[h]));

	for(int h=0; h<H; ++h) \
		for(int w=0; w<W; ++w)\
			if (arr[h][w] == 0) arr[h][w] = MAGIC_NUM;


	int tmp = 0;
	for(int y=0; y<H; ++y) {
		for(int x=0; x<W; ++x) {
			if (MAGIC_NUM == arr[y][x]) 
				continue;

			for(int h=0; h<H; ++h) \
				memset(dp[h], 0, sizeof(dp[h]));

			tmp = __f(y, x, 0);
			ans = MAX(ans, tmp);
			//f(y, x, 0, 0);


		}
	}
	printf("%d\n", ans);
	for(int y=0; y<H; ++y) {
		for(int x=0; x<W; ++x) \
			printf("%d ", dp[y][x]);
		printf("\n");
	}
	printf("-------------------\n");
	for(int y=0; y<H; ++y) {
		for(int x=0; x<W; ++x) \
			printf("%d ", visited[y][x]);
		printf("\n");
	}



	return 0;
}


