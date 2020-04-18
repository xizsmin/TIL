// 1408. String Matching in C - From leetcode

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN		30
#define MAX_ARRAY_LEN	100

char **stringMatching(char **words, int wordsSize, int *returnSize)
{
	// check if words[i] is substring of words[j]
	int i,j;
	int cnt=0;
  
  // Mark if any substring appears
  // warning: a single string could be a substring of more than one string.
	int mark[MAX_ARRAY_LEN];
	memset(mark, 0, MAX_ARRAY_LEN*sizeof(int));
	char **ret = NULL;
	for(i=0; i<wordsSize; i++)
	{
		for (j=0; j<wordsSize; j++) {
			if (i == j) continue;
			if (strlen(words[i]) > strlen(words[j])) continue;
			if (strstr(words[j], words[i]))
			{
//				printf("%s %s\n", words[j], words[i]);
				if (mark[i]) continue;
				++cnt;
				mark[i] = 1;
			}
		}
	}
//	printf("cnt: %d\n", cnt);

	ret = (char **)malloc(cnt * sizeof(char *));
	j=0;
	for(i=0; i<wordsSize; ++i) {
		if (mark[i]) {
			ret[j] = words[i];
			++j;
		}
	}
	*returnSize = cnt;
	return ret;
}


int main(int argc, char **argv)
{
	int i;
  
  // input examples:
	char *words[4] = { "mass", "as", "hero", "superhero" };
	int wordsSize = 4;
	//char *words[3] = {"leetcode", "et", "code"}; 
	//int wordsSize = 3;
	//char *words[3] = {"blue", "green", "bu" };
	//int wordsSize = 3;

	int returnSize = -1;

	char ** ret = stringMatching(words, wordsSize, &returnSize);
	printf("%d\n", returnSize);
	for(i=0; i<returnSize; ++i) \
		printf("%s ", ret[i]);
	printf("\n");
	return 0;
}
