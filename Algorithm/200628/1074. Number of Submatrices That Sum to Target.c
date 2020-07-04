//
// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
// Time Limit Exceeds ㅡㅡ

#define N_MAX		300
#define M_MAX		300
int subm[N_MAX][M_MAX];

int numSubmatrixSumTarget(int** matrix, int matrixSize, int* matrixColSize, int target){
    int N=matrixSize;
    int M=matrixColSize[0];
    for (int n=0; n<N_MAX; ++n)
        memset(subm[n], 0, sizeof(subm[n]));
    
	subm[0][0] = matrix[0][0];
    
	for (int i=1; i<N; ++i) {
		subm[i][0] = subm[i-1][0] + matrix[i][0];
    }

	for (int i=1; i<M; ++i) {
		subm[0][i] = subm[0][i-1] + matrix[0][i];
	}

	for (int n=1; n<N; ++n) {
		for( int m=1; m<M; ++m) {
			subm[n][m] = matrix[n][m] + subm[n][m-1]+ subm[n-1][m] -subm[n-1][m-1];
		}
	}
    
	int cnt=0;
	int tmp;
	for(int y=0; y<N; ++y) {
		for( int x=0; x<M; ++x) {
			for(int i=0; i<=y; ++i) {
				for (int j=0; j<=x; ++j) {
                    int a = (j > 0 ? subm[y][j-1] : 0);
                    int b = (i > 0 ? subm[i-1][x] : 0);
                    int c = ((i>0 && j>0)? subm[i-1][j-1] : 0);
                    //tmp = subm[y][x]-subm[y][j-1]-subm[i-1][x]+subm[i-1][j-1];
                    tmp = subm[y][x]-a-b+c;
                    if (tmp == target) ++cnt;
                    
				}
			}
		}
	}
	return cnt;
    
}

