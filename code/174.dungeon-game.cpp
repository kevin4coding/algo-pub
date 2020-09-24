class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    const int R = std::size(dungeon);
    const int C = std::size(dungeon[0]);

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

    mempool.reset(R, C);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == R - 1 and j == C - 1) {
            return dungeon[i][j] <= 0 ? -dungeon[i][j] + 1 : 1;
          }
          else if (i == R - 1 and j < C - 1) {
            return std::max(f(i, j + 1) - dungeon[i][j],  1);
          }
          else if (i < R - 1 and j == C - 1) {
            return std::max(f(i + 1, j) - dungeon[i][j], 1);
          }
          else if (i < R - 1 and j < C - 1) {
            return std::max(std::min(f(i + 1, j), f(i, j + 1)) - dungeon[i][j], 1);
          }
          throw std::logic_error({});
        }());
      }
    };

    return f(0, 0);
  }
};
