class Solution {
public:
    string smallestFromLeaf(TreeNode* root) {
      
      const auto solution = [&](std::string self = std::string(1, 'a' + 26)) {
        std::function<void(TreeNode*, TreeNode*)> fold = [&, acc = std::string{}](TreeNode* n, TreeNode * prev) mutable {
          if (n == nullptr) {
            std::reverse(std::begin(acc), std::end(acc));
            if (prev->left == nullptr and prev->right == nullptr)
              self = std::min(self, acc);
            std::reverse(std::begin(acc), std::end(acc));
          }
          else {
            acc.push_back((char)n->val + 'a');
            fold(n->left, n);
            fold(n->right, n);
            acc.pop_back();
          }
        };
        return fold(root, nullptr), self;
      }();
      
      return solution;
    }
};
