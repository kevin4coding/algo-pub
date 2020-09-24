class Solution {
 public:
  vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
    std::function<TreeNode*(TreeNode*)> clone = [&](TreeNode* n) {
      if (n == nullptr) {
        return static_cast<TreeNode*>(nullptr);
      }
      else {
        return new TreeNode(n->val, clone(n->left), clone(n->right));
      }
    };
    
    const auto solution = [&](std::vector<int> self = {}) {
      std::function<void(TreeNode*)> fold = [&, id = int(0)](TreeNode* n) mutable {
        if (n == nullptr or self == std::vector<int>{-1}) {
          return;
        }
        else {
          if (n->val != voyage[id]) {
            std::exchange(self, {-1});
          }
          if (n->left and n->left->val != voyage[id + 1]) {
            self.emplace_back(n->val);              
            std::swap(n->left, n->right);
          }
          std::exchange(id, id + 1);
          fold(n->left);
          fold(n->right);
        }
      };
      // let the original tree be immutable
      return fold(clone(root)), self;
    }();

    return solution;
  }
};
