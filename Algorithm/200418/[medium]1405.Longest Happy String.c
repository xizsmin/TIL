// TBD: Time exceed-
// Pruning - just greedily try the longest choice as possible
//
// The next step can be determined
// to compare the priority of a, b, c under given condition.
// i.e., no need to go through all cases.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cnt=0;

int endswith(const char *str, const char *suffix)
{
	int str_len = strlen(str);
	int suffix_len = strlen(suffix);

	if (suffix_len > str_len) return 0;
	if(0== strncmp(str+(str_len-suffix_len), suffix, suffix_len))
		return 1;
	return 0;
}


#define MAX(x, y)			( (x) > (y) ? (x) : (y) )
int max_len = 0;
char ans[301];

int get_largest(int x, int y, int z)
{
	int ret = x;
	if (ret < y) ret = y;
	if (ret < z) ret = z;
	return ret;
}

void f(int a, int b, int c, char *ret)
{
	if (a == 0 && b == 0 && c == 0) {
		//printf("%s\n", ret);
		if (strlen(ans) < strlen(ret)) {
		//	ans = ret;
			memcpy(ans, ret, strlen(ret));

			max_len = strlen(ret);
			ans[max_len] = '\0';
		}
		memset(ret, '\0', sizeof(ret));
		++cnt;

		return;
	}
	int len = strlen(ret);

	if (max_len < strlen(ret)) {
		max_len = strlen(ret);
		memcpy(ans, ret, strlen(ret));
		ans[max_len] = '\0';
	}

	char *p = ret;
	p += (len);


	int l = get_largest(a, b, c);
	if (a>0) {
		if (!endswith(ret, "aa")) {
			f(a-1, b, c, strcat(ret, "a"));//, lev+1);
			*p = '\0';
		}
	}

	if (b>0) {
		if (!endswith(ret, "bb")){
			f(a, b-1, c, strcat(ret, "b"));//, lev+1); 
			*p = '\0';
		}
	}

	if (c>0){
		if (!endswith(ret, "cc")) {
			f(a, b, c-1, strcat(ret, "c"));//, lev+1);
			*p = '\0';
		}
	}

/*	
	if (a>0) {
		if (!endswith(ret, "aa")) {
			f(a-1, b, c, strcat(ret, "a"));//, lev+1);
			*p = '\0';
		}
	}

	if (b>0) {
		if (!endswith(ret, "bb")){
			f(a, b-1, c, strcat(ret, "b"));//, lev+1); 
			*p = '\0';
		}
	}

	if (c>0){
		if (!endswith(ret, "cc")) {
			f(a, b, c-1, strcat(ret, "c"));//, lev+1);
			*p = '\0';
		}
	}*/
}



char *longestDiverseString(int a, int b, int c)
{
	char ret1[101];
	char ret2[101];
	char ret3[101];
	max_len = 0;


	memset(ret1, '\0', sizeof(ret1));
	memset(ret2, '\0', sizeof(ret2));
	memset(ret3, '\0', sizeof(ret3));
	memset(ans, '\0', sizeof(ans)); 

	ret1[0] = 'a', ret2[0] = 'b', ret3[0] = 'c';
	if (a > 0) f(a-1, b, c, ret1);
	if (b > 0) f(a, b-1, c, ret2);
	if (c > 0) f(a, b, c-1, ret3);

	return ans;
}

int main(void)
{
	int N;
	int a, b, c;

	scanf("%d", &N);
	for(int n=0; n<N; ++n) {
		scanf("%d", &a);
		scanf("%d", &b);
		scanf("%d", &c);


		printf("%d %d %d\n", a, b, c);
		printf("%s\n", longestDiverseString(a,b,c));

	}

//	printf("%s\n", longestDiverseString(7,1,0));
	return 0;
}
