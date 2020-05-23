
#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y)		( (x) > (y) ? (x) : (y) )
#define N_MAX			100000

int N;
int visited[N_MAX];

struct node {
	int val;
	int child_len;
	struct node **children;
}; 
struct node *nodes;

void insert(struct node *head, struct node *n) {
	head->children = (struct node **)realloc(head->children, (head->child_len+1)*sizeof(struct node *));
	head->children[head->child_len] = n;
	head->child_len++;
}	

int ans = 0;
void g(int *manager, int *informTime, struct node *cur, int cost)
{
	ans = MAX(ans, cost);

	for(int i=0; i<cur->child_len; ++i) {

		if (visited[cur->children[i]->val]) continue;
		visited[cur->children[i]->val] = 1;
		g(manager, informTime, cur->children[i], cost + informTime[cur->val]);
	}
}


int numOfMinutes(int n, int headID, int* manager, int managerSize, int* informTime, int informTimeSize){ 
    N = n;
    ans = 0;
    memset(visited, 0, sizeof(visited));
    nodes = (struct node *)malloc(sizeof(struct node) * N);
    for(int n=0; n<N; ++n) \
        nodes[n].val = n, nodes[n].child_len = 0, nodes[n].children = NULL;
    for(int n=0; n<N; ++n) { 
        if (manager[n] == -1) continue;
        insert(&nodes[manager[n]], &nodes[n]);
    }
    
    g(manager, informTime, &nodes[headID], 0);
    for(int n=0; n<N; ++n ){
        free(nodes[n].children);
    }
    free(nodes);
    return ans;
}
