class Solution {
 public:
  vector<vector<int>> levelOrder(Node* root) {
    const auto candidate = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      std::function<void(Node*, int)> fold = [&](Node* n, int level) {
        if (n == nullptr) {
          return;
        }
        else {
          self[level].emplace_back(n->val);
          for (const auto ch : n->children) {
            fold(ch, level + 1);
          }
        }
      };
      return fold(root, 0), self;
    }();

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(std::size(candidate));
      for (const auto & [level, nodes] : candidate) {
        std::copy(std::begin(nodes), std::end(nodes), std::back_inserter(self[level]));
      }
      return self;
    }();

    return solution;    
  }
};
