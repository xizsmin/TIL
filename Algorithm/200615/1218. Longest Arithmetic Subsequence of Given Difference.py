class Solution:
      
    def longestSubsequence(self, arr: List[int], difference: int) -> int:
        loc_dict = { arr[i]:[] for i in range(len(arr)) }
        cnt_dict = { k:1 for k in arr }
        
        for i in range(len(arr)):
            loc_dict[arr[i]].append(i)
            
        ret = 1
        for i in range(len(arr)):
            if (arr[i] - difference) in loc_dict:
                if min(loc_dict[arr[i]-difference]) < i:
                    cnt_dict[arr[i]] = max(cnt_dict[arr[i]], cnt_dict[arr[i]-difference]+1)
                ret = max(ret, cnt_dict[arr[i]])
                
        return ret
    
    
