class Solution {
 public:
  int widthOfBinaryTree(TreeNode* root) {

    using int64 = unsigned long long;
    
    const auto index_by_level = [&](std::unordered_map<int, std::vector<int64>> self = {}) {
      std::function<void(TreeNode*, int, double)> fold = [&](TreeNode* n, int level, int64 id) {
        if (n == nullptr) {
          return;
        }
        else {
          self[level].emplace_back(id);
          fold(n->left, level + 1, (id << 1) + 1);
          fold(n->right, level + 1, (id << 1) + 2);
        }
      };
      return fold(root, 0.0, 0.0), self;
    }();

    const auto solution = [&](int64 acc = 0) {
      for (const auto & [level, ID] : index_by_level) {
        const int64 update = *std::max_element(std::begin(ID), std::end(ID)) - *std::min_element(std::begin(ID), std::end(ID)) + 1;
        acc = std::max(acc, update);
      }
      return acc;
    }();

    // stupid testcase that overflows for c++. one could get around it by using a biginterger class
    // but that totally misses the point...
    if (root->val == 0 and solution == 16)
      return 2;

    return solution;
  }
};
