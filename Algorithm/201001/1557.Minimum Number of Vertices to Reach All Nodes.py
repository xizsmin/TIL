# https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/

class Solution:
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:
        #nodes = [x for x in range(0, n)]
        introv_nodes = set(e[1] for e in edges)
        nodes = set(range(0,n))
        ret = list(nodes - introv_nodes)
            
        return ret
