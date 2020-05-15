// TBD: apply DP!

#define MAX(x, y)			( (x) > (y) ? (x) : (y) )

int max_val = 0;
int N;

  
void f(int *slices, int slicesSize, int idx, int sum, int psum, int cnt)
{
	if (cnt == N || idx == slicesSize) {
		max_val = MAX(max_val, sum);
		return;
	}
	if(sum == psum) {
		f(slices, slicesSize, idx+1, sum + slices[idx], sum, cnt+1);
		f(slices, slicesSize, idx+1, sum, sum, cnt);
	} else {
		f(slices, slicesSize, idx+1, sum, sum, cnt);
	}
}


int maxSizeSlices(int* slices, int slicesSize){
    N = slicesSize / 3;
    f(slices, slicesSize, 0, 0, 0, 0);
    return max_val;
}

