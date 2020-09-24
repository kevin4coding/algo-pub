class Solution {
 public:
  int splitArray(vector<int>& nums, int m) {
    const int n = std::size(nums);
    
    const auto prefix_sum = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        self[i] = nums[i] + (i == 0 ? 0 : self[i - 1]);
      }
      return self;
    }();
    
    auto RMQ = [&](int i, int j) {
      return prefix_sum[j] - (i == 0 ? 0 : prefix_sum[i - 1]);
    };
    
    auto make_f = [&](std::vector<std::vector<int>> f = {}) {
      f.resize(n, std::vector<int>(m + 1, INT_MAX));
      for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
          if (j == 1) {
            f[i][j] = RMQ(0, i);
          }
          else {
            f[i][j] = [&](int acc = INT_MAX) {
              for (int k = j - 1; k <= i; ++k) {
                acc = std::min(acc, std::max(RMQ(k, i), f[k - 1][j - 1]));
              }
              return acc;
            }();
          }
        }
      }
      return f;
    };

    const auto f = make_f();

    return f[n - 1][m];
  }
};
