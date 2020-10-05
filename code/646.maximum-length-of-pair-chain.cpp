class Solution {
 public:
  int findLongestChain(vector<vector<int>>& pairs) {
    const int n = std::size(pairs);

    const auto sorted_pairs = [&](std::vector<std::vector<int>> self = {}) {
      std::copy(std::begin(pairs), std::end(pairs), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    auto solve = [&]() {
      struct {
        mutable std::vector<std::vector<int>> pile = {};
      } ST;
      
      for (int i = 0; i < n; ++i) {
        if (std::empty(ST.pile) or sorted_pairs[i][0] > ST.pile.back()[1]) {
          ST.pile.emplace_back(sorted_pairs[i]);
        }
        else if (sorted_pairs[i][1] < ST.pile.back()[1]) {
          ST.pile.back() = sorted_pairs[i];
        }
      }

      return std::size(ST.pile);
    };

    return solve();
  }
};
