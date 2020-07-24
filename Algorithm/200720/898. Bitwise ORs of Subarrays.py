#https://leetcode.com/problems/bitwise-ors-of-subarrays/

'''
하나씩 다 해보기
모든 원소에 대해서 순차적으로
(새로운 집합) = (기존에 만들었던 or 집합) | 자기 자신  + 자기 자신
-> 집합 사이즈가 클 것 같지만 32비트 한정이므로 n^2 보다 작게 나옴(사실상 32n)
'''

class Solution:
    def subarrayBitwiseORs(self, A: List[int]) -> int:
        ret = set()
        cur = set()
        for n in A:
            cur = { n|x for x in cur } | {n}
            ret |= cur
        return len(ret)
        
