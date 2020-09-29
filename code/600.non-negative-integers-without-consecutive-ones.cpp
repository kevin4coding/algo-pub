class Solution {
 public:
  int findIntegers(int num) {
    struct {
      mutable std::optional<int> f[40] = {};
    } mempool;


    auto binary = [&](std::vector<int> self = {}) {
      for (auto [i, d] = std::pair{0, 1}; d <= num; ++i, d <<= 1) {
        self.emplace_back(0 < (d & num));
      }
      return self;
    }();

    const int n = std::size(binary);
        
    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 1;
          }
          else if (i == 1) {
            return 2;
          }
          else {
            return f(i - 1) + f(i - 2);
          }
        }());
      }
    };

    std::function<int(int)> g = [&](int i) {
      if (i == 0) {
        return binary[i] == 0 ? 1 : 2;
      }
      else if (binary[i] == 1 and binary[i - 1] == 0) {
        return f(i) + g(i - 1);
      }
      else if (binary[i] == 1 and binary[i - 1] == 1) {
        return f(i) + f(i - 1);
      }
      else if (binary[i] == 0) {
        return g(i - 1);
      }
      throw;
    };

    return g(n - 1);

  }
};
