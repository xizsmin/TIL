"""
https://leetcode.com/problems/maximum-subarray/

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

"""

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        ans = -10000
        cur = 0
      
        for i in range(0, len(nums)):
            cur = cur + nums[i]
            if (ans < cur):
                ans = cur
 
            if cur < 0:
                cur = 0  
            
        return ans
      
      
