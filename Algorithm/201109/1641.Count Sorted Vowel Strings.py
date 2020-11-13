# https://leetcode.com/problems/count-sorted-vowel-strings/

'''
Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) 
and are lexicographically sorted.
A string s is lexicographically sorted if for all valid i, 
s[i] is the same as or comes before s[i+1] in the alphabet.

TRICK:
  Just count them all, with applying DP for performance.
  
  f(x, n) = Sum[f(i, n-1)] where 0<=i<=4 and x >= i
  
'''


dp = [[]]

def f(x, n) -> int:
    
    if dp[x][n] != -1:
        return dp[x][n]
    if n == 1:
        dp[x][n] = 1
        return 1
    
    
    dp[x][n] = 0
    for i in range(1, 6):
        if i > x:
            continue
        dp[x][n] += f(i, n-1)
        
    return dp[x][n]
        
class Solution:
    def countVowelStrings(self, n: int) -> int:
        ans = 0
        dp.clear()
        
        for i in range(1, 7):
            dp.append([-1 for x in range(0, n+1)])
        
        for i in range(1, 6):
            ans += f(i, n)
            
        return ans
        
        
        
