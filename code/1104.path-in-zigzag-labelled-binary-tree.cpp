class Solution {
 public:
  vector<int> pathInZigZagTree(int label) {
    auto next_pow2 = [](int x) {
      std::function<int(int)> solve = [&](int acc) {
        return acc > x ? acc : solve(acc << 1);
      };
      return solve(1);
    };

    auto prev_pow2 = [](int x) {
      std::function<int(int)> solve = [&](int acc) {
        return acc * 2 > x ? acc : solve(acc << 1);
      };
      return solve(1);
    };

    const auto solution = [&](std::vector<int> self = {}) {
      std::function<void(int)> fmap = [&](int x) {
        const auto p = next_pow2(x);
        if (x == 1) {
          self.emplace_back(x);
          std::reverse(std::begin(self), std::end(self));
          return;
        }
        else if (p % 2 == 0) {
          self.emplace_back(x);
          fmap((prev_pow2(x) + (next_pow2(x) - 1 - x)) / 2);
        }
        else {
          self.emplace_back(x);
          fmap(next_pow2(x / 2) - 1 - ((x / 2) - prev_pow2(x / 2)));
        }
      };
      return fmap(label), self;
    }();

    return solution;
  }
};
