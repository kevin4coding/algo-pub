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
    void flatten(TreeNode* root) {


      std::function<TreeNode*(TreeNode*)> go = [&](TreeNode* node) {
        if (node == nullptr) {
          return static_cast<TreeNode*>(nullptr);
        }
        else if (node->left == nullptr and node->right == nullptr) {
          return node;
        }
        else if (const auto [lch, rch] = std::pair{node->left, node->right}; node->left == nullptr and node->right != nullptr) {
            const auto last_rch = go(rch);
            node->right = rch;
            return last_rch;
        }
        else if (node->left != nullptr and node->right == nullptr) {
          node->left = nullptr;
          const auto last_lch = go(lch);
          node->right = lch;
          return last_lch;
        }
        else {
          node->left = nullptr;
          const auto last_lch = go(lch);
          node->right = lch;
          const auto last_rch = go(rch);
          last_lch->right = rch;
          return last_rch;
        }
      };
      
      go(root);
    }
};

