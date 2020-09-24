class Solution {
 public:
  bool isCompleteTree(TreeNode* root) {
    const auto solution = [&](bool self = false) {
      std::function<void(void)> bfs = [&, Q = std::deque<TreeNode*>{root}]() mutable {
        if (Q.front() == nullptr) {
          std::exchange(self, std::count_if(std::begin(Q), std::end(Q), [&](auto x) {
            return x != nullptr;
          }) == 0);
          return;
        }
        else {
          const auto n = Q.front();
          Q.pop_front();
          Q.emplace_back(n->left);
          Q.emplace_back(n->right);
          bfs();
        }
      };

      return bfs(), self;
    }();
   
    return solution;
  }
};
