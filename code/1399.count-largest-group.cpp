class Solution {
 public:
  int countLargestGroup(int n) {
    std::function<int(int)> f = [&](int x) {
      if (x == 0) {
        return 0;
      }
      else {
        return x % 10 + f(x / 10);
      }
    };

    const auto freq_map = [&](std::unordered_map<int, int> self = {}) {
      for (int i = 1; i <= n; ++i) {
        self[f(i)]++;
      }
      return self;
    }();

    const auto max_group_size = [&](int acc = 0) {
      for (const auto & [val, cnt] : freq_map) {
        acc = std::max(cnt, acc);
      }
      return acc;
    }();

    const auto solution = [&](int acc = 0) {
      for (const auto & [val, cnt] : freq_map) {
        if (cnt == max_group_size) {
          ++acc;
        }
      }
      return acc;
    }();

    return solution;
  }
};
