class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    const int n = std::size(nums);
    static struct {
      mutable std::optional<int> f[5000];

      void reset(int r) {
        for (int i = 0; i <= r; ++i) {
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
              for (int k = 0; k < i; ++k) {
                if (nums[k] < nums[i]) {
                  acc = std::max(acc, 1 + f(k));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      mempool.reset(n);
      for (int i = 0; i < n; ++i) {
        acc = std::max(acc, f(i));
      }
      return acc;
    };

    return solve();
    
  }
};
