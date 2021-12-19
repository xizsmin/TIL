"""
https://leetcode.com/problems/maximum-depth-of-binary-tree/

Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: 3
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        
        queue = [(root, 1)]
        ret = 1
        
        while len(queue) > 0:
            x = queue.pop()
            
            ret = max(ret, x[1])
            if x[0].left != None:
                queue.append((x[0].left, x[1]+1))
                             
            if x[0].right != None:
                queue.append((x[0].right, x[1]+1))
                
        return ret
      
      
