/*
Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.



Example 1:

Input: nums = [2,2,3,2] Output: 3 

Example 2:

Input: nums = [0,1,0,1,0,1,99] Output: 99 



*/

int singleNumber(int* nums, int numsSize){
    int one = 0, two = 0;
    for (int i = 0; i < numsSize; i++) {
        int one_ = (one ^ nums[i]) & ~two;
        int two_ = nums[i] & one | ~nums[i] & two;
        one = one_;
        two = two_;
    }
    return one;
}
