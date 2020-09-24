class Solution {
 public:
  TreeNode* insertIntoBST(TreeNode* root, int val) {
    std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        std::exchange(root, new TreeNode(val));
      }
      else {

        if (n->val > val) {
          if (n->left == nullptr) {
            std::exchange(n->left, new TreeNode(val));
          }
          else {
            fold(n->left);
          }
        }
        else {
          if (n->right == nullptr) {
            std::exchange(n->right, new TreeNode(val));
          }
          else {
            fold(n->right);
          }
        }
      }
    };
    return fold(root), root;
  }
};
