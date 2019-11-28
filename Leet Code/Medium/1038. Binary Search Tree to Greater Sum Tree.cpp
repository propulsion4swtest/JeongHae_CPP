/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    void PostOrder(TreeNode *node, int *value){
        if(node->right != NULL)
            PostOrder(node->right, value);
        
        *value += node->val;
        node->val = *value;
        //cout << node->val << endl;
        
        if(node->left != NULL)
            PostOrder(node->left, value);
    }
    
    TreeNode* bstToGst(TreeNode* root) {
        int value = 0;
        PostOrder(root, &value);
        
        return root;
    }
};
