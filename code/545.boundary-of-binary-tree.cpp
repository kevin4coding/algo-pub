class Solution {
 public:
  vector<int> boundaryOfBinaryTree(TreeNode* root) {
    const auto left_boundary = [&](std::vector<TreeNode*> self = {}) {
    std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        return;
      }
      else {
        self.emplace_back(n);
        if (n == root) {
          fold(n->left);
        }
        else if (n->left != nullptr) {
          fold(n->left);
        }
        else if (n->right != nullptr) {
          fold(n->right);
        }
      }
    };
    return fold(root), self;
    }();

    const auto right_boundary = [&](std::vector<TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          self.emplace_back(n);
          if (n == root) {
            fold(n->right);
          }
          else if (n->right != nullptr) {
            fold(n->right);
          }
          else if (n->left != nullptr) {
            fold(n->left);
          }
        }
      };
      return fold(root), self;
    }();

    const auto leaves = [&](std::vector<TreeNode*> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int level) {
        if (n == nullptr) {
          return;
        }
        else {
          fold(n->left, level + 1);
          if (n->left == nullptr and n->right == nullptr) {
            self.emplace_back(n);
          }
          fold(n->right, level + 1);
        }
      };
      return fold(root, 1), self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      if (not std::empty(left_boundary)) {
        for (int i = 0; i < std::size(left_boundary); ++i) {
          self.emplace_back(left_boundary[i]->val);
        }
        for (int i = int(left_boundary.back() == leaves.front()); i < std::size(leaves); ++i) {
          self.emplace_back(leaves[i]->val);
        }
        for (int i = std::size(right_boundary) - 1 - int(leaves.back() == right_boundary.back()); i > 0; --i) {
          self.emplace_back(right_boundary[i]->val);
        }
      }
      return self;
    }();

    return solution;
  }
};
