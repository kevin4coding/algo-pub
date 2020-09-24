class Solution {
 public:
  vector<int> getStrongest(vector<int>& arr, int k) {
    const int n = std::size(arr);
    
    const auto solution = [&](std::vector<int> self = {}) {
      std::copy(std::begin(arr), std::end(arr), std::back_inserter(self));
      std::nth_element(std::begin(self), std::begin(self) + (n - 1) / 2, std::end(self));
      const int m = self[(n - 1) / 2];
      std::sort(std::begin(self), std::end(self), [&](int x, int y) {
        if (std::abs(x - m) == std::abs(y - m))
          return x > y;
        else
          return std::abs(x - m) > std::abs(y - m);
      });
      self.resize(k);
      return self;
    }();

    return solution;
  }
};
