class Solution {
 public:
  bool isValidSequence(TreeNode* root, vector<int>& arr) {
    const int N = std::size(arr);

    auto is_leaf = [&](TreeNode* n) { return n->left == nullptr and n->right == nullptr; };
    
    const auto solution = [&](bool self = false) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int level) {
        if (n == nullptr or self == true) {
          return;
        }
        else {
          self |= is_leaf(n) and (level == N - 1 and n->val == arr[N - 1]);
          if (level < N and n->val == arr[level]) {
            fold(n->left, level + 1);
            fold(n->right, level + 1);
          }
        }
      };
      return fold(root, 0), self;
    }();
    return solution;
  }
};
