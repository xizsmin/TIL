#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x, y)		( (x) > (y) ? (x) : (y) )
#define N_MAX			100

int N,M;
int headID;
int manager[N_MAX+1];
int manager_id[N_MAX+1];
int informTime[N_MAX+1];
int adj[N_MAX][N_MAX];
int visited[N_MAX+1];
int ans = 0;

struct node {
	int idx;
	struct node *next;
};

struct node *node_list;

void dfs(int idx, int cost)
{
	int tmp = 0;
	for(int i=0; i<N; ++i) {
		if (i==headID) ans = MAX(ans, cost);
		if (visited[i] || adj[idx][i]== 0) continue;
		visited[i] = 1;
		dfs(i, cost + adj[idx][i]);
	}
}

void f(int idx, int cost)
{
	int tmp=0;
	for(int i=0; i<N; ++i) {
		if (i == headID) ans = MAX(ans, cost);
		if (visited[i] || manager[i]!= idx) continue;
		visited[i] = 1;
		f(i, cost + informTime[idx]);
	}
}

void g(int idx, int cost)
{
	int tmp=0;

	struct node *p = &node_list[idx];
	while (p->next) {
		if (visited[p->idx]) continue;
		printf("%d -> ", p->idx);
		visited[p->idx] = 1;
		g(p->idx, cost+informTime[idx]);
	}
}

void insert(struct node *cur, int val)
{
	struct node *ret = (struct node *)malloc(sizeof(struct node));
	ret->idx = val; ret->next = NULL;
	cur->next = ret;
}

int main(int argc, char **argv)
{
	scanf("%d", &N);
	scanf("%d", &headID);
	for(int n=0; n<N; ++n) \
		scanf("%d", manager+n);
	for(int n=0; n<N; ++n) \
		scanf("%d", informTime+n);
	memset(manager_id, -1, sizeof(manager_id));

	for(int n=0; n<N; ++n) {
		if (manager[n] == -1) continue;
		manager_id[manager[n]] = 1;
	}
	for(int n=0; n<N; ++n) {
		if (manager_id[n]!= -1) ++M;
	}
	node_list = (struct node *)malloc(sizeof(struct node)*M);
	int m = 0;
	int s = 0;
	printf("M: %d\n", M);
	for(int i=0; i<N; ++i) {
		if (-1 == manager_id[i]) continue;
		if (i == headID) s = m;
		node_list[m].idx = i;
		node_list[m].next= NULL;
		manager_id[i] = m;
		m++;

	}
	for(int m=0; m<M; ++m) \
		printf("%d\n", node_list[m].idx);
	for(int i=0; i<N; ++i) \
		printf("[%d, %d]\n", i, manager_id[i]);


	for(int i=0; i<N; ++i) {
		if (i == headID) continue;
//		adj[manager[i]][i] = informTime[manager[i]];

		struct node *p = &node_list[manager[i]];
		while (p->next) { p = p->next; }
		insert(p, i);

	}
	/*
	for(int m=0; m<M; ++m) {
		struct node *p = &node_list[m];
		while (p) {
			printf("%d -> ", p->idx);
			p = p->next;
		}
		printf("\n");
	}
	printf("s: %d\n", s);
	*/



	//dfs(headID, 0);
	//f(headID, 0);
	g(manager_id[headID], 0);

/*	for(int i=0; i<N; ++i) {
		for(int j=0; j<N; ++j) \
			printf("%d ", adj[i][j]);
		printf("\n");
	}
*/

//	printf("%d\n", ans);

	return 0;
}

