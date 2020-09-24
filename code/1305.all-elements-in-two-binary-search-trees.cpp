class Solution {
 public:
  vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    auto preorder_list = [](TreeNode* root) {
      auto result = std::vector<int>{};
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          fold(n->left);
          result.emplace_back(n->val);
          fold(n->right);
        }
      };
      return fold(root), result;
    };

    auto merge = [](const std::vector<int>&arr1, const std::vector<int>& arr2) {
      const int N1 = std::size(arr1);
      const int N2 = std::size(arr2);
      auto result = std::vector<int>{};
      std::function<void(int, int)> go = [&](int n1, int n2) {
        if (n1 == N1 and n2 == N2) {
          return;
        }
        else if (n1 == N1 and n2 < N2) {
          std::copy(std::begin(arr2) + n2, std::end(arr2), std::back_inserter(result));
          return;
        }
        else if (n1 < N1 and n2 == N2) {
          std::copy(std::begin(arr1) + n1, std::end(arr1), std::back_inserter(result));
          return;
        }
        else {
          if (arr1[n1] <= arr2[n2]) {
            result.emplace_back(arr1[n1]);
            go(n1 + 1, n2);
          }
          else {
            result.emplace_back(arr2[n2]);
            go(n1, n2 + 1);
          }
        }
      };
      return go(0, 0), result;
    };

    return merge(preorder_list(root1), preorder_list(root2));
  }
};
