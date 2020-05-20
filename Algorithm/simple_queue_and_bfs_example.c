#include <stdio.h>
#define N_MAX			1000

struct queue {
	int data[N_MAX];
	int out_offset;
	int in_offset;
	int _offset;
	int _size;

	void (*queue)(struct queue *);
	void (*push)(struct queue*, int);
	int (*pop)(struct queue*);
	int (*empty)(struct queue*);
	void (*print)(struct queue*);
};

void queue(struct queue *q) {
	for (int i=0; i<N_MAX; ++i) q->data[i] = -1;
	q->out_offset = q->in_offset = q->_size = 0;
}

void push(struct queue *q, int item) {
	if(q->_size == N_MAX) {
		printf("Failed to push(): queue is full. abort()\n");
		return;
	}
	q->_size++; q->data[q->in_offset++] = item;
}

int pop(struct queue *q) {
	if (q->empty(q)) {
		printf("Failed to pop(): queue is empty. abort()\n");
		return -1;
	}
	q->_size--;
	int ret = q->data[q->out_offset];
	q->data[q->out_offset++] = -1;
	return ret;
}

int empty(struct queue *q) { return (q->_size==0); }

void print(struct queue *q) {
	for(int i=q->out_offset; i<q->in_offset; ++i) \
		printf("%d ", q->data[i]);
	printf("\n");
}


struct queue q = {
	.queue = queue,
	.push = push,
	.pop = pop,
	.empty = empty,
	.print = print,
};

int visited[N_MAX];
int dist[N_MAX];

int adj[N_MAX][N_MAX] = {\
	{0,1,1,0,0,0,0}, \
	{0,0,0,0,0,1,1}, \
	{0,0,0,1,0,0,0}, \
	{0,1,0,0,1,0,1}, \
	{0,0,0,0,0,0,0}, \
	{0,0,0,0,0,0,1}, \
	{0,0,0,0,0,0,0} \
};


void bfs(int start, const int n)
{
	q.push(&q, start);
	visited[start] = 1;

	while(!q.empty(&q)) {
		int here = q.pop(&q);
		printf("%d -> ", here);
		for(int i=0; i<n; ++i) {
			if (!adj[here][i]) continue;
			q.push(&q, i); visited[i] = 1;
			dist[i] = dist[here] + 1;
		}
	}
	printf("\n");
}

int main(void)
{
	bfs(0, 7);
	printf("[DIST] ");
	for(int i=0; i<7; ++i) \
		printf("%d ", dist[i]);
	printf("\n");
	return 0;
}

