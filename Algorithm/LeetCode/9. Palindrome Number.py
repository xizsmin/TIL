"""
https://leetcode.com/problems/palindrome-number/

Given an integer x, return true if x is palindrome integer.

An integer is a palindrome when it reads the same backward as forward. For example, 121 is palindrome while 123 is not.

 

Example 1:

Input: x = 121
Output: true
Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Example 4:

Input: x = -101
Output: false
"""

class Solution:
    def isPalindrome(self, x: int) -> bool:
        if (x < 0):
            return False
        if (x < 10):
            return True
        
        y = ""
        while x > 0:
            print(x%10)
            y = y + (str(x%10))
            x = int(x / 10)
        #print("y:",y)
        
        for i in range(0, int((len(y)+1)/2)):
            if y[i] != y[len(y)-i-1]:
                return False
        return True
        
        
