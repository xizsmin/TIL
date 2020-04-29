/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int level[10000];
 
void f(struct TreeNode *root, int lev)
{
    if (root == NULL)        return;

    level[lev] += root->val;
    f(root->left, lev+1);
    f(root->right, lev+1);
    
}

int deepestLeavesSum(struct TreeNode* root){
    int ret = -1;
    memset(level, 0, sizeof(int)*10000);
    
    f(root, 0);
    for(int i=9999; i>=0; --i) {
        if (level[i]) {
            ret = level[i];
            break;
        }
    }
    return ret;
}
