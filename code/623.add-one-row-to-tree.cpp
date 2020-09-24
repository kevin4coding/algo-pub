class Solution {
 public:
  TreeNode* addOneRow(TreeNode* root, int v, int d) {
    const auto solution = [&]() {
      std::function<void(TreeNode*, TreeNode*, char, int)> fold = [&](TreeNode* n, TreeNode* prev, char dir, int level) {
        if (n == nullptr) {
          if (level == d) {
            std::exchange(dir == 'r' ? prev->right : prev->left, new TreeNode(v));
          }
          return;
        }
        else {
          if (level == d) {
            if (d == 1) {
              std::exchange(root, new TreeNode(v, root, nullptr));
            }
            else {
              std::exchange(dir == 'r' ? prev->right : prev->left,
                            new TreeNode(v,
                                         dir == 'l' ? n : nullptr,
                                         dir == 'r' ? n : nullptr));
            }
          }
          fold(n->left, n, 'l', level + 1);
          fold(n->right, n, 'r', level + 1);
        }
      };
      return fold(root, nullptr, '!',1), root;
    }();

    return solution;
    
  }
};
