class Solution {
 public:
  int rob(vector<int>& nums) {
    static struct {
      mutable std::optional<int> f[100];

      void reset(int r) {
        for (int i = 0; i < r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    const int n = std::size(nums);

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return nums[i];
          }
          else if (i == 1) {
            return std::max(nums[0], nums[1]);
          }
          else if (i > 1) {
            return std::max(nums[i] + f(i - 2), f(i - 1));
          }
          throw;
        }());
      }
    };
    

    return n == 0 ? 0 : (mempool.reset(n), f(n - 1));
  }
};
