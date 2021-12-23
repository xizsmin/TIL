"""
https://leetcode.com/problems/binary-tree-postorder-traversal/

Given the root of a binary tree, return the postorder traversal of its nodes' values. 

Example 1:


Input: root = [1,null,2,3]
Output: [3,2,1]

"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        
        if root is None:
            return []
        
        ret = []
        ret.extend(self.postorderTraversal(root.left))
        ret.extend(self.postorderTraversal(root.right))
        ret.append(root.val)
        
        return ret
      
      
