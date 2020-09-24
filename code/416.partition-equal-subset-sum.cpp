class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    static const struct {
      mutable std::optional<int> f[200][20000];
    } mempool;

    const auto total_sum = std::accumulate(std::begin(nums), std::end(nums), 0);
    if (total_sum % 2 != 0) {
      return 0;
    }
    const auto target =  total_sum / 2;
    const int n = std::size(nums);

    // clear cache
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < target; ++j) {
        mempool.f[i][j].reset();
      }
    }
    
    std::function<bool(int, int)> f = [&, memo = std::ref(mempool.f)](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return j == 0;
          }
          else if (j == 0) {
            return true;
          }
          else {
            if (j - nums[i] >= 0) {
              return f(i - 1, j - nums[i]) or f(i - 1, j);
            }
            else {
              return f(i - 1, j);
            }
          }
        }());
      }
    };

    return f(n - 1, target);
  }
};
