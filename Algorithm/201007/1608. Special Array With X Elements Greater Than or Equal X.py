# https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/
'''
You are given an array nums of non-negative integers. nums is considered special 
if there exists a number x such that there are exactly x numbers in nums that are greater than or equal to x.
Notice that x does not have to be an element in nums.
Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the value for x is unique.

'''
'''
Algorithm:
1. Let's say desc_nums[] = nums sorted in descending order.
2. Generalization:
   - To say i numbers in nums are greater than or equal to i:
   - we need to see if desc_nums[i-1] >= i. 
   - Now, to ensure that there are EXACTLY i numbers meet the condition,
   - desc_nums[i] must be smaller than i.
e.g.,
   0 1 2 3 4 5
  -------------    => desc_nums[2] > 3 and desc_nums[3] < 3: There are exactly 3 numbers in nums greater than 3
   9 6 4 1 0 0
   
   0 1 2 3 4 5
  -------------    => desc_nums[2] > 3 and desc_nums[3] > 3: 3 can't be answer (No answer exists in this case).
   9 6 4 3 0 0
   
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

    
