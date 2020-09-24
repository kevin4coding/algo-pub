class Solution {
 public:
  TreeNode* removeLeafNodes(TreeNode* root, int target) {
    const auto parent = [&](std::unordered_map<TreeNode*, TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->left != nullptr) {
            self[n->left] = n;
          }
          if (n->right != nullptr) {
            self[n->right] = n;
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        return;
      }
      else {
        fold(n->left);
        fold(n->right);
        if (n->left == nullptr and n->right == nullptr and n->val == target) {
          if (parent.count(n)) {
            if (parent.at(n)->left and parent.at(n)->left == n) {
              parent.at(n)->left = nullptr;
              delete n;
            }
            if (parent.at(n)->right and parent.at(n)->right == n) {
              parent.at(n)->right = nullptr;
              delete n;
            }
          }
          else {
            std::exchange(root, nullptr);
            delete root;
          }
        }
      }
    };

    return fold(root), root;
  }
};
