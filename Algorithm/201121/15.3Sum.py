# https://leetcode.com/problems/3sum/
'''
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.
Notice that the solution set must not contain duplicate triplets.

TRICK:
 - Fix a number and it becomes two sums problem (find exactly two numbers whose sum makes target):
 
 tmp = {}
 target
 for i: 0 -> len(nums)-1
    if nums[target-nums[i]] not in tmp:
        tmp[target-nums[i]] = i
    else:
        return [i, tmp[target-nums[i]]
'''

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        
        if len(nums) < 3:
            return []
        
        if all([_ == 0 for _ in nums]):
            return [[0,0,0]]
        
        if all([_ < 0 for _ in nums]):
            return []
        
        if all([_ > 0 for _ in nums]):
            return []
        
         
        s = 0
        tmp = dict()
        ret = set()
        nums.sort()
        
        while s < len(nums) - 2:
            for i in range(s+1, len(nums)):
                if nums[i] not in tmp:
                    tmp[-1*nums[s]-nums[i]] = i
                else:
                    ret.add(tuple([nums[s], nums[i], -nums[i]-nums[s]]))
                    #tmp = dict()
                    #break
            s += 1
            tmp = dict()
        return ret
                    
