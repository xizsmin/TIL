"""
https://leetcode.com/problems/add-binary/

Given two binary strings a and b, return their sum as a binary string.

 

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
"""

class Solution:
        
    def addBinary(self, a: str, b: str) -> str:
      # Solution 1
        return "{0:b}".format(int(int(a,2) + int(b,2)))
      
      
        """
        # Solution 2
        
        if len(a) > len(b):
            b = "0"*(len(a)-len(b)) + b
        elif len(a) < len(b):
            a = "0"*(len(b)-len(a)) + a
            
        #print(a)
        #print(b)
        ret = ""
        d = 0
        for i in range(len(a)-1, -1, -1):
            x = int(a[i])
            y = int(b[i])
            #print(x, y, d)
            if d == 0:
                ret = ret+(str(x^y))
                d = x and y
            else:
                ret = ret+(str(1-(x^y)))
                d = x or y
        ret = ret[::-1]
        if d > 0:
            ret = str(d) + ret
        return ret
        """
        
        
