class Solution {
 public:
  int rob(vector<int>& nums) {
    static struct {
      mutable std::optional<int> f[100][2] = {};
      
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
          if (n == 1) {
            return nums[0];
          }
          else if (n == 2) {
            return std::max(nums[0], nums[1]);
          }
          else if (j == 0) {
            if (i == 0) {
              return nums[i];
            }
            else if (i == 1) {
              return std::max(nums[0], nums[1]);
            }
            else if (i == n - 1) {
              return f(i - 1, j);
            }
            else {
              return std::max(f(i - 1, j), nums[i] + f(i - 2, j));
            }
          }
          else if (j == 1) {
            if (i == 1) {
              return nums[i];
            }
            else if (i == 2) {
              return std::max(nums[2], nums[1]);
            }
            else {
              return std::max(nums[i] + f(i - 2, j), f(i - 1, j));
            }
          }
          throw;
        }());
      }
    };

    return n == 0 ? 0 : (mempool.reset(n, 2), std::max(f(n - 1, 0), f(n - 1, 1)));

  }
};
