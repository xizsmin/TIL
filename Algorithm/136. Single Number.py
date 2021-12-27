"""
https://leetcode.com/problems/single-number/

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

 

Example 1:

Input: nums = [2,2,1]
Output: 1
"""

class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        ret = 0
        for n in nums:
            ret = ret ^ n
        return ret
        
        #return reduce(lambda i, j: int(i) ^ int(j), nums)
        
        
        
