class Solution {
 public:
  vector<int> countBits(int num) {
    struct {
      mutable std::optional<int> f[100000] = {};
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 0;
          }
          else if (i == 1) {
            return 1;
          }
          else if (i % 2 == 0) {
            return f(i / 2);
          }
          else {
            return f(i - 1) + 1;
          }
        }());
      }
    };

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(num + 1);
      for (int i = 0; i <= num; ++i) {
        self[i] = f(i);
      }
      return self;
    }();

    return solution;
  }
};

