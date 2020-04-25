// optimization required

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *ret;

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    ret = (int *)malloc(sizeof(int)*2);
    *returnSize = 2;
    int i, j, tmp;
    for(i=0; i<numsSize; ++i) {
        tmp = nums[i];
        for(j=i+1; j<numsSize; ++j){
            if (tmp + nums[j] == target)
            {
                ret[0] = i; ret[1] = j;
                
                return ret;
            }
        }
    }
    return NULL;
}

