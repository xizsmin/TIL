# https://leetcode.com/problems/consecutive-characters/


class Solution:
    def maxPower(self, s: str) -> int:
        ret = 1
        tmp = 1
        last = s[0]
        for c in s[1:]:
            if last == c:
                tmp = tmp + 1
            else:
                ret = max(ret, tmp)
                tmp = 1
                last = c
        ret = max(ret, tmp)
        return ret
            
            
