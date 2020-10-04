from collections import Counter
class Solution:
    def maxSumRangeQuery(self, nums: List[int], requests: List[List[int]]) -> int:
        
        index = range(0, len(nums)+1)
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
        
        
