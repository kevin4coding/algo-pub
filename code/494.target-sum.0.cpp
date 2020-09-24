class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int S) {
    if (S >= 2005) {
      return 0;
    }

    const int n = std::size(nums);

    const struct {
      mutable std::unordered_map<int, std::unordered_map<int, std::optional<int>>> f; 
    } mempool;
    
    std::function<int(int, int)> f = [&](int i, int j) {
      auto & memo = mempool.f;
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return static_cast<int>(-nums[i] == j)  + static_cast<int>(nums[i] == j);
          }
          else {
            return f(i - 1, j - nums[i]) + f(i - 1, j + nums[i]);
          }
        }());
      }
    };

    return f(n - 1, S);
  }
};
