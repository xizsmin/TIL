# https://leetcode.com/problems/the-k-strongest-values-in-an-array/

from collections import Counter

class Solution:
    def getStrongest(self, arr: List[int], k: int) -> List[int]: 
        
        _arr = sorted(arr)
        #print(_arr)
        cnt_arr = Counter(_arr)

        median=_arr[int(len(arr)/2-0.5)]
        #print(median)

        d = dict((k, abs(k-median)) for k in _arr)
        #print(d)
        res = sorted(d.items(), key=lambda x:(x[1], x[0]), reverse=True)
        
        
        ret = []
        i=0
        while k > 0:
            n = min(k, cnt_arr[res[i][0]])
            for x in range(n):
                ret.append(res[i][0])
            cnt_arr[res[i][0]] = cnt_arr[res[i][0]]-n
            
            if (cnt_arr[res[i][0]]==0):
                cnt_arr.pop(res[i][0])
                i = i+1
            k=k-n
        return ret
        
