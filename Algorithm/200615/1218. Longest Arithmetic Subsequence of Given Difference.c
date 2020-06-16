 
#define N_MAX			100000
#define MAX(x, y)		( (x) > (y) ? (x) : (y) )


int dp[N_MAX];


int __f(int idx, int *arr, int arrSize, int difference)
{
	if(idx >= arrSize) return 0; 
    
    if (dp[idx]) return dp[idx];

    dp[idx] = 1;
	for(int i=idx+1; i<arrSize; ++i) {
		if (arr[i] - arr[idx] != difference) continue;
        int tmp = __f(i, arr, arrSize, difference)+1;
		dp[idx] = MAX(dp[idx], tmp);
	}
	return dp[idx];
}

 
int longestSubsequence(int* arr, int arrSize, int difference){
    memset(dp, 0, sizeof(dp));
	int ret = 1;
	for(int i=0; i<arrSize; ++i) {
        int tmp = __f(i, arr, arrSize, difference);
		ret = MAX(ret, tmp);
	}
	return ret;

}
