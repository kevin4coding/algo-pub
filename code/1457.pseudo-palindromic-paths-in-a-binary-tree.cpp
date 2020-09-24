class Solution {
 public:
  int pseudoPalindromicPaths (TreeNode* root) {

    auto check = [&](const std::vector<int>& bucket, int n) {
      const auto cnt_odd = std::count_if(std::begin(bucket), std::end(bucket), [&](auto x) {
        return x > 0 and x % 2 == 1;
      });

      const auto cnt_even = std::count_if(std::begin(bucket), std::end(bucket), [&](auto& x) {
        return x > 0 and x % 2 == 0;
      });

      if ((n + 1) % 2 == 0) {
        return cnt_even >= 0 and cnt_odd == 0;
      }
      else {
        return cnt_even >= 0 and cnt_odd == 1;
      }
    };
    
    const auto solution = [&](int acc = 0) {
      std::function<void(TreeNode*, int)> fold = [&, bucket = std::vector<int>(10, 0)](TreeNode* n, int d) mutable {
        if (n == nullptr) {
          return;
        }
        else if (n->left == nullptr and n->right == nullptr) {
          ++bucket[n->val];
          if (check(bucket, d)) {
            ++acc;
          }
          --bucket[n->val];
        }
        else {
          if (n->left != nullptr) {
            ++bucket[n->val];
            fold(n->left, d + 1);
            --bucket[n->val];
          }
          if (n->right != nullptr) {
            ++bucket[n->val];
            fold(n->right, d + 1);
            --bucket[n->val];
          }
        }
      };
      return fold(root, 0), acc;
    }();

    return solution;
  }
};
