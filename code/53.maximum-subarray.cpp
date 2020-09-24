class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    const int n = std::size(nums);
    
    const struct {
      mutable std::optional<int> f[50000];
    } mempool;


    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return nums[0];
          }
          else {
            return std::max(f(i - 1) + nums[i], nums[i]);
          }
        }());
      }
    };

    const auto solution = [&](int acc = INT_MIN) {
      for (int i = 0; i < n; ++i) {
        acc = std::max(acc, f(i));
      }
      return acc;
    }();

    return solution;

  }
};
