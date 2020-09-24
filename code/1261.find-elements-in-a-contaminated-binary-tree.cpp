class FindElements {
 private:
  mutable std::unordered_set<int> value_;
  
 public:
  FindElements(TreeNode* root) : value_{} {
    std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int id) {
      if (n == nullptr) {
        return;
      }
      else {
        value_.emplace(id);
        std::exchange(n->val, id);
        fold(n->left, id * 2 + 1);
        fold(n->right, id * 2 + 2);
      }
    };
    fold(root, 0);
  }
    
  bool find(int target) {
    return static_cast<bool>(value_.count(target));
  }
};
