class Solution {
 public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    const auto solution = [&](std::optional<TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) 
          return;
        else 
          return p->val < n->val ? (self.emplace(n), fold(n->left)) : (fold(n->right));
      };
      return fold(root), self;
    }();
    return solution.value_or(nullptr);
  };
};
