class Solution {
 public:
  int wiggleMaxLength(vector<int>& nums) {
    static struct {
      mutable std::optional<int> f[10000][2] = {};

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < 2; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;


    const int n = std::size(nums);
    const static int INC = 0;
    const static int DEC = 1;
    
    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return 1;
          }
          else if (j == INC) {
            return [&](int acc = 0) {
              for (int k = 0; k <= i - 1; ++k) {
                if (nums[k] < nums[i]) {
                  acc = std::max(acc, 1 + f(k, DEC));
                }
              }
              return acc;
            }();
          }
          else if (j == DEC) {
            return [&](int acc = 0) {
              for (int k = 0; k <= i - 1; ++k) {
                if (nums[k] > nums[i]) {
                  acc = std::max(acc, 1 + f(k, INC));
                }
              }
              return acc;
            }();
          }
          else throw;
        }());
      }
        
    };

    auto solve = [&](int acc = 0) {
      mempool.reset(n, 2);
      for (int i = 0; i < n; ++i) {
        acc = std::max({acc, f(i, INC), f(i, DEC)});
      }
      return acc;
    };

    return solve();
        
      
  }
};
