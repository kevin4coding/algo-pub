class Solution {
 public:
  vector<int> preorderTraversal(TreeNode* root) {
    auto concat = [&](std::vector<int>&& v1, const std::vector<int>& v2) {
      std::copy(std::begin(v2), std::end(v2), std::back_inserter(v1));
      return std::move(v1);
    };
    
    std::function<std::vector<int>(TreeNode*)> fold = [&](TreeNode* node) {
      if (node == nullptr) {
        return std::vector<int>{};
      }
      else {
        return concat(std::vector<int>{node->val}, concat(fold(node->left), fold(node->right)));
      }
    };    
    return fold(root);
  }
};
