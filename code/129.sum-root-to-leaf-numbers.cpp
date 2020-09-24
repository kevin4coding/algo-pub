class Solution {
 public:
  int sumNumbers(TreeNode* root) {
    std::function<int(TreeNode*, int)> fold = [&](TreeNode* node, int init) {
      if (node == nullptr) {
        return 0;
      }
      else if (node->left == nullptr and node->right == nullptr) {
        return (10 * init + node->val);
      }
      else {
        return fold(node->left, 10 * init + node->val) + fold(node->right, 10 * init + node->val);
      }
    };
    return fold(root, 0);
  }
};
