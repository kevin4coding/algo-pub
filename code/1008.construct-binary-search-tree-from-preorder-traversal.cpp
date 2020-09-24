class Solution {
 public:
  TreeNode* bstFromPreorder(vector<int>& preorder) {
    const int n_tree = std::size(preorder);
    
    std::function<TreeNode*(int, int)> fold = [&, idx = 0](int lower, int upper) mutable {
      if (idx == n_tree or preorder[idx] < lower || preorder[idx] > upper)
        return static_cast<TreeNode*>(nullptr);
      else {
        return new TreeNode(preorder[idx++], fold(lower, preorder[idx - 1]), fold(preorder[idx - 1], upper));
      }
    };
    return fold(INT_MIN, INT_MAX);
  }
};
