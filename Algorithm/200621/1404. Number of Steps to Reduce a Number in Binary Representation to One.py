# simple fairly simple simulation

def inc(n: str):
    num = list(n)
    
    i=len(num)-1
    while(i >= 0 and num[i] != '0'):
        num[i]='0'
        i=i-1
    if (i >= 0 and num[i] == '0'):
        num[i] = '1'
    ret = ''.join(num)
    if(num[0] == '0'):
        ret = '1' + ''.join(num)
    return ret

class Solution:
    def numSteps(self, s: str) -> int:
        if s == '1':
            return 0
    
        elif s[-1] == '1':
            return Solution.numSteps(self,inc(s))+1

        elif s[-1] == '0':
            cnt=0
            while s[-1] == '0':
                cnt=cnt+1
                s=s[:-1]
            return Solution.numSteps(self,s)+cnt
