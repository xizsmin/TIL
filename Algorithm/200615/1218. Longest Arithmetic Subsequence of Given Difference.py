class Solution:
    
    def __init__(self):
        self.dp={}
        self.visited=[]

    def f(self, _list, _visited, item, diff):
        if _list is None:
            return 0
        if item in self.dp:
            return self.dp[item]
        ret = 1
        
        for x in _list: 
            if (x in _visited) :
                continue
            if (x - item == diff) :
                _visited.append(x)
                ret = max(ret, self.f(_list, _visited, x, diff)+1)

        self.dp[item] = ret
        return ret 
    
    def longestSubsequence(self, arr: List[int], difference: int) -> int:
        ret = 1
        cnt=1
        for i in arr:
            visited = []
            visited.append(i)
            tmp_arr = arr[cnt:]
            ret = max(ret, self.f(tmp_arr, visited, i, difference))
            cnt = cnt + 1
        return ret
