"""
https://leetcode.com/problems/valid-parentheses/

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

=> O(N)
"""

class Solution:
        
    def isValid(self, s: str) -> bool:
        if len(s) > 0 and (s[0] == ')' or s[0] == '}' or s[0] == ']'):
            return False
        
        buf = []
        for i in range(0, len(s)):
            if s[i] == '(' or s[i] == '[' or s[i] == '{':
                buf.append(s[i])
            elif s[i] == ')' and buf and buf[-1] == '(': 
                buf.pop()
            elif s[i] == '}' and buf and buf[-1] == '{': 
                buf.pop()
            elif s[i] == ']' and buf and buf[-1] == '[': 
                buf.pop()
            else:
                return False
                #buf.append(s[i])
                
        if not buf:
            return True
        return False
                
            
