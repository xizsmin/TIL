
// 최소 부분합 구하기

#define MIN(x, y)           ( (x) < (y) ? (x) : (y) )
#define MAX(x, y)           ( (x) > (y) ? (x) : (y) )
int minStartValue(int* nums, int numsSize){
    int min = nums[0];
    int acc = nums[0]; 
    for(int i=1; i<numsSize; ++i) {
        acc += nums[i];
        min = MIN(min, acc);
    }
    return MAX(1, min*(-1)+1);
}
