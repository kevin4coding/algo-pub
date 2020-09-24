class Solution {
 public:
  vector<TreeNode*> splitBST(TreeNode* root, int V) {
    
    std::function<std::vector<TreeNode*>(TreeNode*, int)> fold = [&](TreeNode* n, int v) ->std::vector<TreeNode*> {
      if (n == nullptr) {
        return std::vector<TreeNode*>{nullptr, nullptr};
      }
      else {
        if (n->val == v) {
          return {new TreeNode(n->val, n->left, nullptr), n->right};
        }
        else if (n->val < v) {
          const auto R = fold(n->right, v);
          return {new TreeNode(n->val, n->left, R[0]), R[1]};
        }
        else {
          const auto L = fold(n->left, v);
          return {L[0], new TreeNode(n->val, L[1], n->right)};
        }
      }
    };
    return fold(root, V);
  }
};
