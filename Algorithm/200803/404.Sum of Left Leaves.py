'''
Left leaves 따라가며 합 구하기
** Right child도 방문해야 함
cf. level order -> bfs(queue) 
'''


class Solution:
    def sumOfLeftLeaves(self, root: TreeNode) -> int:
        if(root is None):
            return 0
        ret = 0        
        tmp = 0
        if(root.left is not None):
            if root.left.left is None and root.left.right is None:
                tmp= root.left.val
            ret += (tmp + self.sumOfLeftLeaves(root.left))
        if(root.right is not None):        
            ret += self.sumOfLeftLeaves(root.right)
        return ret
        
