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
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:

    def f(self, rootA, rootB):
        if rootA == None and rootB == None:
            return True
        
        if rootA != None and rootB != None:
            if rootA.val == rootB.val:
                return self.f(rootA.left, rootB.right) and self.f(rootA.right, rootB.left)
        return False
    
    
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        if root is None:
            return True
        if root.left is None and root.right is not None:
            return False
        if root.left is not None and root.right is None:
            return False
        if root.left is None and root.right is None:
            return True
        
        return self.f(root.left, root.right)
    
    
