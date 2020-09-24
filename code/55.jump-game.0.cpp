class Solution {
 public:
  bool canJump(vector<int>& nums) {
    const int n = std::size(nums);
    
    const struct {
      mutable std::optional<int> f[30000];
    } mempool;

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return nums[0];
          }
          else if (f(i - 1) < i) {
            return f(i - 1);
          }
          else {
            return std::max(f(i - 1), nums[i] + i);
          }
        }());
      }
    };

    const auto solution = [&](bool acc = false) {
      for (int i = 0; i < n and not acc; ++i) {
        acc |= (f(i) >= n - 1);
      }
      return acc;
    }();

    return solution;
  }
};
