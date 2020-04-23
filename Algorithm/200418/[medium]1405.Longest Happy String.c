// wrong algorithm
// counter-example: 4 15 7 -> must be length of 26


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(x, y, t)		((t)=(x),(x)=(y),(y)=(t))


char str[301] = {'\0',};
int a, b, c;

struct count {
	char letter;
	int cnt;
} typedef COUNT;

COUNT cntarr[3];

void sort_cntarr()
{
	COUNT tmp;
	for(int i=0; i<3; ++i) {
		for (int j=i+1; j<3; ++j) {
			if (cntarr[i].cnt < cntarr[j].cnt)
				swap(cntarr[i], cntarr[j], tmp);
		}
	}

//	for (int i=0; i<3; ++i) \
		printf("%c %d\n", cntarr[i].letter, cntarr[i].cnt);
}

int endswith(char c, int repeat)
{
	int len = strlen(str);
	if (len < repeat) return 0;
	for (int i=0; i<repeat; ++i) \
		if (str[len-i-1] != c) return 0;
	return 1;
}

int state[3];

void f()
{
	while (1) {
		sort_cntarr();
		int changed = 0;
		for (int i=0; i<3; ++i) if (state[i] != cntarr[i].cnt) changed = 1;
		if (!changed) return;
		for(int i=0; i<3; ++i) state[i] = cntarr[i].cnt;

//		printf("[%c]%d, [%c]%d, [%c]%d\n", cntarr[0].letter, cntarr[0].cnt, cntarr[1].letter, cntarr[1].cnt, cntarr[2].letter, cntarr[2].cnt);
		if (cntarr[0].cnt == 0) return;
		for(int i=0; i<3; ++i) {
			if (cntarr[i].cnt == 0) continue;
			if (endswith(cntarr[i].letter, 2)) continue;

			int len = strlen(str);
			if (endswith(cntarr[i].letter, 1)) {
				//printf("(1)\n");
				str[len]=cntarr[i].letter;
				cntarr[i].cnt--;
				break;
			}
			else {
				if (cntarr[i].cnt >= 2)
				{
					//printf("(2)\n");
					str[len] = cntarr[i].letter;
					str[len+1] = cntarr[i].letter;
					cntarr[i].cnt--;
					cntarr[i].cnt--;
					break;
				} else { 
					//printf("(3)\n");
					str[len] = cntarr[i].letter; cntarr[i].cnt--; 
					break;
				}
			}

		} //printf("%s\n-------------------------------\n", str);

	}

}

char *wrapper()
{
	cntarr[0].letter='a'; cntarr[0].cnt = a;
	cntarr[1].letter='b'; cntarr[1].cnt = b;
	cntarr[2].letter='c'; cntarr[2].cnt = c;

	f();
	return str;
}

int main(void)
{
	int N;
	scanf("%d", &N);
	for(int n=0; n<N; ++n) {
		memset(str, '\0', sizeof(str));

		scanf("%d", &a); scanf("%d", &b); scanf("%d", &c); 

		//sort_cntarr();
		printf("%s\n", wrapper());

	}

	return 0;
}
