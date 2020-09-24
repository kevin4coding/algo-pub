class Solution {
 public:
  int numberOfPatterns(int m, int n) {
    static struct {
      std::optional<int> f[(1 << 10)][10][10] = {};

      void reset(int r, int c, int l) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            for( int k = 0; k < l; ++k) {
              f[i][j][k].reset();
            }
          }
        }
      }
      
    } mempool;

    mempool.reset(1 << 10, 10, 10);
    
    const auto blocks = [&](std::vector<std::vector<std::optional<int>>> self = {}) {
      self.resize(10, std::vector<std::optional<int>>(10, std::optional<int>{}));
      self[1][9] = 5; self[1][3] = 2; self[1][7] = 4;
      self[2][8] = 5;
      self[3][1] = 2; self[3][7] = 5; self[3][9] = 6;
      self[4][6] = 5;
      self[6][4] = 5;
      self[7][1] = 4; self[7][3] = 5; self[7][9] = 8;
      self[8][2] = 5;
      self[9][7] = 8; self[9][3] = 6; self[9][1] = 5;
      return self;
    }();

    
    std::function<int(int, int, int)> f = [&, memo = mempool.f](int S, int k, int remain) {
      if (memo[S][k][remain].has_value()) {
        return memo[S][k][remain].value();
      }
      else {
        return memo[S][k][remain].emplace([&] {
          if (remain == 1) {
            return 1;
          }
          else {
            return [&](int acc = 0) {
              for (int i = 1; i <= 9; ++i) {
                if (not (S & (1 << i)) and (not blocks[k][i].has_value() or ((1 << blocks[k][i].value()) & S))) {
                  acc += f(S | (1 << i), i, remain - 1);
                }
              }
                  return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      for (int k = m; k <= n; ++k) {
        for (int i = 1; i <= 9; ++i) {
          acc += f((1 << i), i, k);
        }
      }
      return acc;
    };

    return solve();
  }
};
