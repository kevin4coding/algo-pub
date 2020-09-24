class Solution {
 public:
  int countNodes(TreeNode* root) {
    std::function<int(TreeNode*)> fold = [&](TreeNode* node) {
      if (node == nullptr) {
        return 0;
      }
      else {
        return 1 + fold(node->left) + fold(node->right);
      }
    };
    return fold(root);
  }
};
