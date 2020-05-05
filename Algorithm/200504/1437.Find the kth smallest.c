

bool kLengthApart(int* nums, int numsSize, int k){
    int gap = 0;
    int init=0;
    while (nums[init] == 0) {
        ++init;
        if (init == numsSize) break;
    }
    if (init == numsSize) return true;
    
    for(int i=init; i<numsSize; ++i) {
        if (nums[i] == 1 && i != init) {
            if (gap < k) return false;
            gap = 0;
        }
        else gap++;
    }
    return true;
}
