class Solution:
    def flip(self, num):
        return 1 if num == 0 else 0
    def flipAndInvertImage(self, A: List[List[int]]) -> List[List[int]]:
        ret = []
        for l in A:
            l.reverse()
            l = [self.flip(x) for x in l ]
            ret.append(l)
        #print(ret)
        return ret
