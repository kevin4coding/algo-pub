class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    static struct {
      mutable std::optional<int> f[500][500] = {};

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    const int n = std::size(nums);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          const auto ll = i == 0 ? 1 : nums[i - 1];
          const auto rr = j == n - 1 ? 1 : nums[j + 1];
          if (i == j) {
            return nums[i] * ll * rr;
          }
          else {
            return [&](int acc = 0) {
              for (int k = i; k <= j; ++k) {
                if (k == i) {
                  acc = std::max(acc, nums[k] * ll * rr + f(k + 1, j));
                }
                else if (k == j) {
                  acc = std::max(acc, f(i, k - 1) + nums[k] * ll * rr);
                }
                else if (k > i and k < j) {
                  acc = std::max(acc, nums[k] * ll * rr + f(i, k - 1) + f(k + 1, j));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return n == 0 ? 0 : (mempool.reset(n, n), f(0, n - 1));    
  }
};
