"""
https://leetcode.com/problems/move-zeroes/

Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

 

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 10^4
-231 <= nums[i] <= 2^31 - 1
"""

class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        i = 0 
        
        cnt = 0
        while i < len(nums):
            if nums[i] == 0:
                cnt = cnt + 1
                nums.pop(i)
            else:
                i = i + 1
                
        for c in range(cnt):
            nums.append(0)
                
