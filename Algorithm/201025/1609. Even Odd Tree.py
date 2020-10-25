# https://leetcode.com/problems/even-odd-tree/

'''
A binary tree is named Even-Odd if it meets the following conditions:

The root of the binary tree is at level index 0, its children are at level index 1, their children are at level index 2, etc.
For every even-indexed level, all nodes at the level have odd integer values in strictly increasing order (from left to right).
For every odd-indexed level, all nodes at the level have even integer values in strictly decreasing order (from left to right).
Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.
'''

'''
Level Order Traversal over Binary Trees ===> BFS ! 

For given root of a binary tree:

q.push(root)
while ! q.empty() :
  x = q.pop()
  print x
  if x.left:
    q.push(x.left)
  if x.right:
    q.push(x.right)

'''

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

def strictlyOddIncreasing(l: list) -> bool:
    if l[0] % 2 == 0:
        return False
    for i in range(1, len(l)):
        if l[i] % 2 == 0:
            return False
        
        if l[i] <= l[i-1]:
            return False
    return True

def strictlyEvenDecreasing(l: list) -> bool:
    if l[0] % 2 == 1:
        return False
    for i in range(1, len(l)):
        if l[i] %2 == 1:
            return False
        if l[i] >= l[i-1]:
            return False
    return True

class Solution:
    def isEvenOddTree(self, root: TreeNode) -> bool:
        deq = collections.deque()
        deq.append((root, 0))
        ret = []
        lev=0
        
        while len(deq) > 0 :
            x = deq.popleft()
            lev = max(lev, x[1])
            ret.append((x[1] , x[0].val))
            if x[0].left:
                deq.append((x[0].left, x[1]+1))

            if x[0].right:
                deq.append((x[0].right, x[1]+1))

        lev=0
        tmplist = []
        
        for r in ret:
            if lev < r[0]:
                if (lev % 2) == 0 and strictlyOddIncreasing(tmplist) == False:
                    return False 
                elif (lev % 2) == 1 and strictlyEvenDecreasing(tmplist) == False:
                    return False 
                lev += 1
                tmplist.clear()
            tmplist.append(r[1])

        if (lev % 2) == 0 and strictlyOddIncreasing(tmplist) == False:
            return False 
        elif (lev % 2) == 1 and strictlyEvenDecreasing(tmplist) == False:
            return False 
                
        return True
                
                
