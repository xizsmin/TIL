"""
https://leetcode.com/problems/symmetric-tree/

Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
"""
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def preorder(self, root):
        if root is None:
            return []
        
        ret = []
        ret.extend(self.preorder(root.left))
        ret.append(root.val)
        ret.extend(self.preorder(root.right))
        
        return ret
        
    def symmetric_preorder(self, root):
        if root is None:
            return []
        
        ret = []
        ret.extend(self.symmetric_preorder(root.right))
        ret.append(root.val)
        ret.extend(self.symmetric_preorder(root.left))

        return ret
    
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        if root is None:
            return True
        if root.left is None and root.right is not None:
            return False
        if root.left is not None and root.right is None:
            return False
        if root.left is None and root.right is None:
            return True
        
        a = self.preorder(root)
        
        b = self.symmetric_preorder(root)
        print(a)
        print(b)
        
        return (self.preorder(root) == self.symmetric_preorder(root))
      
      
