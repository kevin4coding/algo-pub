class Solution {
 public:
  bool canJump(vector<int>& nums) {
    const struct {
      mutable std::optional<bool> f[30005];
    } mempool;

    const int n = std::size(nums);

    std::function<bool(int)> f = [&, memo = std::ref(mempool.f)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return true;
          }
          else {
            return [&](bool acc = false) {
              for (int j = 0; j < i; ++j) {
                acc |= (nums[j] + j >= i and f(j) == true);
              }
              return acc;
            }();
          }
        }());
      }
    };

    return f(n - 1);
  }
};
