class Solution {
 public:
  vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    const auto D = [&](std::unordered_set<int> self = {}) {
      std::copy(std::begin(to_delete), std::end(to_delete), std::inserter(self, std::begin(self)));
      return self;
    }();
    
    const auto parent_map = [&](std::unordered_map<TreeNode*, TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold_build = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n == root) {
            self[n] = nullptr;
          }
          if (n->left != nullptr) {
            self[n->left] = n;
          }
          if (n->right != nullptr) {
            self[n->right] = n;
          }
          fold_build(n->left);
          fold_build(n->right);
        }
      };

      std::function<void(TreeNode*)> fold_del = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (D.count(n->val)) {
            if (self[n] != nullptr) {
              if (self[n]->right != nullptr and self[n]->right == n) {
                self[n]->right = nullptr;
              }
              else if (self[n]->left != nullptr and self[n]->left == n) {
                self[n]->left = nullptr;
              }
            }
            self.erase(n);
            if (n->left != nullptr) {
              self[n->left] = nullptr;
            }
            if (n->right != nullptr) {
              self[n->right] = nullptr;
            }
          }
          fold_del(n->left);
          fold_del(n->right);
        }
      };
      return fold_build(root), fold_del(root), self;
    }();


    const auto solution = [&](std::vector<TreeNode*> self = {}) {
      for (const auto [node, parent] : parent_map) {
        if (parent == nullptr) {
          self.emplace_back(node);
        }
      }
      return self;
    }();
      
    return solution;
    
  }
};
