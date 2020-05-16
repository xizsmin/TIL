/**
  *  f(idx, cnt, first) = MAX( f(idx+2, cnt+1, first) + arr[idx],  
  *                             f(idx+1, cnt, first) )
**/


int dp[1000][1000][2];
 
int N;

#define MAX(x, y)			( (x) > (y) ? (x) : (y) )
   
int f(int *slices, int slicesSize, int idx, int cnt, int first)
{
    if (first) {
        if (cnt == N || idx >= slicesSize - 1) return 0;
    }
    if (cnt == N || idx >= slicesSize) return 0;
    if (dp[idx][cnt][first] != -1) return dp[idx][cnt][first];
    
    return dp[idx][cnt][first] = MAX(f(slices, slicesSize, idx+2, cnt+1, first) + slices[idx], \
                             f(slices, slicesSize, idx+1, cnt, first));
}
 
int maxSizeSlices(int* slices, int slicesSize){
    N = slicesSize / 3;
    for(int i=0; i<1000; ++i) \
        for(int j=0; j<1000; ++j)
            dp[i][j][0] = -1, dp[i][j][1] = -1;
    
    int ret= MAX(f(slices, slicesSize, 1, 0, 0), f(slices, slicesSize, 0, 0 ,1));
    
    return ret;
}

