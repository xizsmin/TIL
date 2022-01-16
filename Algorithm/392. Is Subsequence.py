"""
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true
Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false

"""

class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        if len(s) > len(t):
            return False
        if s == t:
            return True

        if len(s) == 0:
            return True
        
        while len(t) > 0:
            if len(s) == 0:
                return True
            
            if s[0] == t[0]:
                s = s[1:]
            t = t[1:]
            
        return len(s) == 0
      
      
