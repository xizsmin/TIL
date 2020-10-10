# https://leetcode.com/problems/bulb-switcher-iv/submissions/
'''
There is a room with n bulbs, numbered from 0 to n-1, arranged in a row from left to right. Initially all the bulbs are turned off.

Your task is to obtain the configuration represented by target where target[i] is '1' if the i-th bulb is turned on and is '0' if it is turned off.

You have a switch to flip the state of the bulb, a flip operation is defined as follows:

Choose any bulb (index i) of your current configuration.
Flip each bulb from index i to n-1.
When any bulb is flipped it means that if it is 0 it changes to 1 and if it is 1 it changes to 0.

Return the minimum number of flips required to form target.
'''

'''
TRICK:
   - We need to flip the bulb everytime we encounter one in a different state:
   - i.e., we must check every bulb in different state with the previous one.
'''
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
        
