class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    std::function<TreeNode*(TreeNode*)> fold = [&](TreeNode* node) {
      if (std::min(p->val, q->val) <= node->val and std::max(p->val, q->val) >= node->val) {
        return node;
      }
      else if (node->val < std::min(p->val, q->val)) {
        return fold(node->right);
      }
      else {
        return fold(node->left);
      }
    };
    return fold(root);
  }
};
