"""
https://leetcode.com/problems/power-of-four/

Given an integer n, return true if it is a power of four. Otherwise, return false.

An integer n is a power of four, if there exists an integer x such that n == 4x.

 

Example 1:

Input: n = 16
Output: true
Example 2:

Input: n = 5
Output: false
Example 3:

Input: n = 1
Output: true
"""

class Solution:
    def isPowerOfFour(self, n: int) -> bool: 
        if n == 1:
            return True
        if n <= 0:
            return False
        
        while n > 4:
            if n % 4 > 0:
                return False
            n = int(n / 4)
            
        return n == 4
      
      
