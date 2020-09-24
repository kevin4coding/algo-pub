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
  vector<vector<int>> levelOrder(TreeNode* root) {
    auto make_candidate = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      std::function<void(TreeNode*, int)> go = [&](TreeNode* node, int level) {
        if (node == nullptr) {
          return;
        }
        else {
          self[level].emplace_back(node->val);
          go(node->left, level + 1);
          go(node->right, level + 1);
        }
      };
      return go(root, 0), self;
    };

    const auto solution = [&, candidate = make_candidate()](std::vector<std::vector<int>> self = {}) {
      self.resize(std::size(candidate));
      for (const auto & [level, nodes] : candidate) {
        std::copy(std::begin(nodes), std::end(nodes), std::back_inserter(self[level]));
      }
      return self;
    }();

    return solution;
  }
};
