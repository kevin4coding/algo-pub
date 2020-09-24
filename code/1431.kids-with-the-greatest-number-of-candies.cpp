class Solution {
 public:
  vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    const int n = std::size(candies);
    const auto max_candies = *std::max_element(std::begin(candies), std::end(candies));

    const auto solution = [&](std::vector<bool> self = {}) {
      self.resize(n, false);
      for (int i = 0; i < n; ++i) {
        self[i] = ((candies[i] + extraCandies) >= max_candies);
      }
      return self;
    }();

    return solution;
  }
};
