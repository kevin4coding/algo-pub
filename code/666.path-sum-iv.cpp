class Solution {
 public:
  int pathSum(vector<int>& nums) {
    const auto T = [&](std::vector<std::optional<int>> self = {}) {
      self.resize(32, std::optional<int>{});
      for (const auto x : nums) {
        const auto [depth, id, val] = std::tuple{x / 100, (x / 10) % 10, x % 10};
        self[static_cast<int>(std::pow(2, depth - 1)) - 1 + id - 1].emplace(val);
      }
      return self;
    }();

    const auto solution = [&](int acc = 0) {
      std::function<void(int, int)> fold = [&](int i, int subacc_sum) {
        if (not T[i].has_value()) {
          return;
        }
        else if (not T[2 * i + 1].has_value() and not T[2 * i + 2].has_value()) {
          acc += subacc_sum + T[i].value();
        }
        else {
          fold(2 * i + 1, subacc_sum + T[i].value());
          fold(2 * i + 2, subacc_sum + T[i].value());
        }
      };
      return fold(0, 0), acc;
    }();

    return solution;
  }
};
