class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int S) {
    const int n = std::size(nums);

    if (S >= 2005) {
      return 0;
    }

    const struct {
      mutable std::optional<int> f[20][5000];
    } mempool;

    std::function<int(int, int)> f = [&, memo = std::ref(mempool.f)](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return static_cast<int>(-nums[i] + 2000 == j) + static_cast<int>(nums[i] + 2000 == j);
          }
          else {
            return f(i - 1, j - nums[i]) + f(i - 1, j + nums[i]);
          }
        }());
      }
    };

    return f(n - 1, S + 2000);
  }
};
