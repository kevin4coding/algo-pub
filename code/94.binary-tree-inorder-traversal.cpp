/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
 public:
  vector<int> inorderTraversal(TreeNode* root) {
    const auto solution = [&](std::vector<int> self = {}) {
      std::function<void(TreeNode*)> go = [&](TreeNode * root) {
        if (root == nullptr)
          return;
        go(root->left);
        self.emplace_back(root->val);
        go(root->right);
      };
      return go(root), self;
    }();

    return solution;
  }
};
