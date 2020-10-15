
'''
Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:

|---|---|---|---|---|---|
0   1   2   3   4   5   6

Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.

You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. 
When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). 
Please refer to the first example for a better explanation.

Return the minimum total cost of the cuts.
'''

'''
TRICK:

f(s, e) = min(f(s, i) + f(i, e) + (e-s)) for i:0 -> len(cuts)-1
* append start and ending point to cuts[] for convenience.

e.g.,
n=7, cuts=[1,3,4,5]:
f(0, 7) = min(
		f(0, 1) + f(1, 7),
		f(0, 3) + f(3, 7),
		f(0, 4) + f(4, 7),
		f(0, 5) + f(5, 7)
		) + 7
		

'''

class Solution:
    def __init__(self):
        self.dp = []
        self.N_MAX = 200		# a rough maximum...
        self.INT_MAX = 2147483400
    
    def f(self, s, e, cuts):
        #print(s, ',',e)
        if self.dp[s][e] != self.INT_MAX:
            return self.dp[s][e]
        if s == e:
            self.dp[s][e] = 0
            return 0
        for i in range(0, len(cuts)):
            if (cuts[i] < cuts[s] or cuts[i] > cuts[e]):
                continue
            if cuts[s] == cuts[i] or cuts[e] == cuts[i]:
                continue
            self.dp[s][e] = min(self.dp[s][e], self.f(s, i, cuts)+self.f(i, e, cuts)+(cuts[e]-cuts[s]))
        return self.dp[s][e]
        
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts.append(0)
        cuts.append(n)
        cuts = sorted(cuts)
        
        self.dp = [ [self.INT_MAX for i in range(0, self.N_MAX)] for j in range(0, self.N_MAX)]
        for i in range(0, len(cuts)-1):
            self.dp[i][i+1] = 0
            
        return self.f(0, len(cuts)-1, cuts)

