
#define MAX(x, y)   ( (x) > (y) ? (x) : (y) )

int findLengthOfLCIS(int* nums, int numsSize){
    if (numsSize <= 1) return numsSize;
    int ret = 1;
    int tmp = 1;
    for(int i=1; i<numsSize; ++i) {
        if (nums[i] <= nums[i-1]) {
            ret = MAX(ret, tmp);
            tmp = 1;
        } else tmp++;
    }
    ret = MAX(ret, tmp);
    
    return ret;

}
