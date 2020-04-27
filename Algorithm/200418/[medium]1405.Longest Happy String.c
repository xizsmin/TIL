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


void f()
{
	int len;
	int changed = 0;
	while(1) {
		changed = 0;
		sort_cntarr();
		if (cntarr[0].cnt == 0) break;
		len = strlen(str);
		if (len < 2) {
			for(int i=0; i<3; ++i) {
				if (len == 1 && str[len-1] == cntarr[i].letter) continue;
				if (cntarr[i].cnt == 1) {
					str[len] = cntarr[i].letter, cntarr[i].cnt--; changed = 1;break;
				}
				else if (cntarr[i].cnt >= 2) {
					str[len] = cntarr[i].letter, str[len+1] = cntarr[i].letter; cntarr[i].cnt-=2; changed = 1;break;
				}
			}
		} else {
			if (str[len-1] != str[len-2]) {
				for(int i=0; i<3; ++i) {
					//if (str[len-1] == cntarr[i].letter) continue;
					if (cntarr[i].cnt >= 2) {
						if (str[len-1] != cntarr[i].letter) {
							str[len] = cntarr[i].letter;
							str[len+1] = cntarr[i].letter;
							cntarr[i].cnt -= 2;
							changed = 1;
						} else {
							str[len] = cntarr[i].letter;
							cntarr[i].cnt--;
							changed = 1;
						}
						break;
					} else if (cntarr[i].cnt > 0) {
						str[len] = cntarr[i].letter;
						cntarr[i].cnt--;
						changed = 1;
						break;
					}
				}
			} else {
				for(int i=0; i<3; ++i) {
					if (str[len-1] == cntarr[i].letter) continue;
					if (cntarr[i].cnt > 0) {
						str[len] = cntarr[i].letter;
						cntarr[i].cnt--;
						changed = 1;
						break;
					}
				}
			}
		}
//		printf("%s[%c:%d %c:%d %c:%d]\n", str, cntarr[0].letter, cntarr[0].cnt, cntarr[1].letter, cntarr[1].cnt,
//		cntarr[2].letter, cntarr[2].cnt);
		if (!changed) break;
	}
}

char *longestDiverseString(int a, int b, int c)
{
	memset(str, '\0', sizeof(str));
	cntarr[0].letter='a'; cntarr[0].cnt = a;
	cntarr[1].letter='b'; cntarr[1].cnt = b;
	cntarr[2].letter='c'; cntarr[2].cnt = c;
	f();
	return str;
}
