'''
	dp[x] = Max(dp[x-cost[i]]*10 + i+1)
'''


class Solution:
    def largestNumber(self, cost: List[int], target: int) -> str:
        dp = [-1]*5001
        dp[0] = 0
        
        for x in range(1, target+1):
            for i,c in enumerate(cost):
                if x < c or dp[x-c] == -1: 
                    continue
                tmp = dp[x-c]*10+i+1
                dp[x] = tmp if dp[x]<tmp else dp[x]
                     
        return "0" if dp[target] == -1 else str(dp[target])
        
		
