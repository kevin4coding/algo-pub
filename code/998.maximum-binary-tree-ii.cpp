class Solution {
 public:
  TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    std::function<TreeNode*(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        return new TreeNode(val);
      }
      else {
        if (n->val < val) {
          return new TreeNode(val, n, nullptr);
        }
        else {
          return new TreeNode(n->val, n->left, fold(n->right));
        }
      }
    };

    return fold(root);
  }
};
