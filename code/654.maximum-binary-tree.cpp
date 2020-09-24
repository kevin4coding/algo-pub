class Solution {
 public:
  TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    const int n = std::size(nums);
    
     const auto node = [&](std::vector<TreeNode*> self = {}) {
      std::transform(std::begin(nums), std::end(nums), std::back_inserter(self), [&](auto x) {
        return new TreeNode(x);
      });
      return self;
    }();
    
    const auto PGE = [&, DQ = std::deque<TreeNode*>{}](std::unordered_map<TreeNode*, TreeNode*> self = {}) mutable {
      for (int i = 0; i < n; ++i) {
        while (not std::empty(DQ) and DQ.front()->val < node[i]->val) {
          DQ.pop_front();
        }
        if (not std::empty(DQ)) {
          self[node[i]] = DQ.front();
        }
        DQ.emplace_front(node[i]);
      }
      return self;
    }();

    const auto NGE = [&, DQ = std::deque<TreeNode*>{}](std::unordered_map<TreeNode*, TreeNode*> self = {}) mutable {
      for (int i = n - 1; i >= 0; --i) {
        while (not std::empty(DQ) and DQ.front()->val < node[i]->val) {
          DQ.pop_front();
        }
        if (not std::empty(DQ)) {
          self[node[i]] = DQ.front();
        }
        DQ.emplace_front(node[i]);
      }
      return self;
    }();

    const auto solution = [&](TreeNode* self = nullptr) {
      for (int i = 0; i < n; ++i) {
        if (not PGE.count(node[i]) and not NGE.count(node[i])) {
          std::exchange(self, node[i]);
        }
        else if (PGE.count(node[i]) and not NGE.count(node[i])) {
          PGE.at(node[i])->right = node[i];
        }
        else if (not PGE.count(node[i]) and NGE.count(node[i])) {
          NGE.at(node[i])->left = node[i];
        }
        else if (PGE.count(node[i]) and NGE.count(node[i])) {
          if (PGE.at(node[i])->val < NGE.at(node[i])->val) {
            PGE.at(node[i])->right = node[i];
          }
          else {
            NGE.at(node[i])->left = node[i];
          }
        }
      }
      return self;
    }();

    return solution;
  }
};
