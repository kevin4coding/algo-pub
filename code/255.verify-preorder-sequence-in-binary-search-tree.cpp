class Solution {
 public:
  bool verifyPreorder(vector<int>& preorder) {
    const int n = std::size(preorder);
    
    const auto solution = [&, DQ = std::deque<int>{}, root_val = INT_MIN](bool acc = true) mutable {
      for (int i = 0; i < n; ++i) {
        acc &= (preorder[i] >= root_val);
        while (not std::empty(DQ) and preorder[i] > DQ.front()) {
          root_val = std::max(root_val, DQ.front());
          DQ.pop_front();
        }
        DQ.emplace_front(preorder[i]);
      }
      return acc;
    }();

    return solution;
  }
};
