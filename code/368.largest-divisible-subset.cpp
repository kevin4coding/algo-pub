class Solution {
 public:
  vector<int> largestDivisibleSubset(vector<int>& nums) {
    if (std::empty(nums)) {
      return {};
    }
    
    const int n = std::size(nums);

    const auto sorted_nums = [&](std::vector<int> self = {}) {
      std::copy(std::begin(nums), std::end(nums), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    static struct {
      mutable std::optional<int> f[2000] = {};

      void reset(int r) {
        for (int i = 0; i < r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 1;
          }
          else {
            return [&](int acc = 1) {
              for (int j = i - 1; j >= 0; --j) {
                if (sorted_nums[i] % sorted_nums[j] == 0) {
                  acc = std::max(acc, 1 + f(j));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    mempool.reset(n);

    const auto max_info = [&](std::pair<int, int> self = {}) {
      self = {INT_MIN, -1};
      for (int i = 0; i < n; ++i) {
        if (f(i) > self.first) {
          self.first = f(i);
          self.second = i;
        }
      }
      return self;
    }();

    auto solve = [&](std::vector<int> acc = {}) {

      std::function<void(int)> trace_f = [&](int i) {
        if (f(i) == 1) {
          acc.emplace_back(sorted_nums[i]);
          return;
        }
        else {
          for (int j = i - 1; j >= 0; --j) {
            if (sorted_nums[i] % sorted_nums[j] == 0 and f(j) + 1 == f(i)) {
              acc.emplace_back(sorted_nums[i]);
              return trace_f(j);
            }
          }
        }
      };
      return trace_f(max_info.second), acc;
    };

    return solve();
  }
};


