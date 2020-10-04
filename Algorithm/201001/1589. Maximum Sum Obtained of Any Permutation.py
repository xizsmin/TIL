
# https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/
'''
We have an array of integers, nums, and an array of requests where requests[i] = [starti, endi]. 
The ith request asks for the sum of nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi]. Both starti and endi are 0-indexed.
Return the maximum total sum of all requests among all permutations of nums.
Since the answer may be too large, return it modulo 109 + 7.
'''

'''
Algorithm:
  1. Consider a set of points in range 0 ~ nums.length - 1.
  2. Count the number of times each point appears in the ranges stated by requests.
     e.g., [1, 3]: point 1, 2, 3 appears once each.
     Let cnt[] the list to store the result.
  3. Sort cnt[] in descending order of the appearance(frequency).
  4. Sort nums[] in descending order.
  5. return sum(nums[i]*cnt[i]) where 0 <= i < nums.length
  
  
** POINT: TRICK TO GET CNT[] IN O(N)
  
  cnt[] = {0, } of length |nums|+1
  for each req in requests:
    cnt[req[0]] += 1
    cnt[req[1] + 1] -= 1    // !!!!
    
  foreach i: 1...|cnt|
    cnt[i] += cnt[i-1]
    
'''

class Solution:
    def maxSumRangeQuery(self, nums: List[int], requests: List[List[int]]) -> int:
        
        index = range(0, len(nums)+1)     # To keep the original indices after sorting cnt[] desc.
        cnt = [0 for _ in range(0, len(nums)+1)]
        for r in requests:
            cnt[r[0]] += 1
            cnt[r[1]+1] -= 1
            
        for i in range(1, len(cnt)):
            cnt[i] += cnt[i-1]       
            
        _req = dict(zip(index[:-1], cnt[:-1]))

        _req = {k: v for k, v in sorted(_req.items(), key=lambda item: item[1], reverse=True)}
        nums = sorted(nums, reverse=True)
        _new_cnt = list(_req.keys()) 
        _new_order = dict(zip(_new_cnt, nums)) 
        ret = 0
        a1 = list(_new_order.values())
        a2 = list(_req.values())
        for i in range(0, len(a1)):
            x = a1[i] * a2[i]
            x = x % 1000000007
            ret = ret + x
            ret = ret % 1000000007
                  
        return ret
        
        
