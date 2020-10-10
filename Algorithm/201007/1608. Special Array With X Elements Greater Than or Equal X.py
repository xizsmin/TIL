# https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/
'''
You are given an array nums of non-negative integers. nums is considered special 
if there exists a number x such that there are exactly x numbers in nums that are greater than or equal to x.
Notice that x does not have to be an element in nums.
Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the value for x is unique.

'''
class Solution:
    def specialArray(self, nums: List[int]) -> int:
        
        nums = sorted(nums, reverse=True)
        ans = -1
        if len(nums) == 1:
            return 1 if nums[0] >= 1 else -1
        for i in range(len(nums), 1, -1):
            if nums[i-1] >= i:
                if i == (len(nums)) or (nums[i] < i):
                    ans = i
                break
        return ans
