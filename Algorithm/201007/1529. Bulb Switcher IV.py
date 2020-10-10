# https://leetcode.com/problems/bulb-switcher-iv/submissions/


class Solution:
    def minFlips(self, target: str) -> int:
        cnt = 0
        _target = []
        _target[:] = target
        if _target[0] == '1':
            cnt = 1
        for i in range(0, len(_target)-1):
            if _target[i] != _target[i+1]:
                cnt += 1
        return cnt
        
