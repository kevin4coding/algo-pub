class Solution {
 public:
  vector<int> sumZero(int n) {
    const auto solution = [&](std::vector<int> self = {}) {
      if (n % 2 == 0) {
        for (int i = 1; i <= n / 2; ++i) {
          self.emplace_back(-i);
        }
        for (int i = 1; i <= n / 2; ++i) {
          self.emplace_back(i);
        }
      }
      else if (n % 2 == 1) {
        for (int i = 1; i <= (n - 1) / 2; ++i) {
          self.emplace_back(-i);
        }
        for (int i = 1; i <= (n - 1) / 2; ++i) {
          self.emplace_back(i);
        }
        self.emplace_back(0);
      }
      return self;
    }();

    return solution;
  }
};
