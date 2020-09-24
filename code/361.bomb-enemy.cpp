class Solution {
 public:
  int maxKilledEnemies(vector<vector<char>>& grid) {
    if (std::empty(grid)) return 0;

    const int R = std::size(grid);
    const int C = std::size(grid[0]);

    const int ll = 0, rr = 1, uu = 2, dd = 3;

    const int dr[4] = {0, 0, -1, 1};
    const int dc[4] = {-1, 1, 0, 0};

    static struct {
      mutable std::optional<int> f[500][500][4] = {};

      void reset(int r, int c, int l) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            for (int k = 0; k < l; ++k) {
              f[i][j][k].reset();
            }
          }
        }
      }
    } mempool;


    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    std::function<int(int, int, int)> f = [&, memo = mempool.f](int i, int j, int d) {
      if (memo[i][j][d].has_value()) {
        return memo[i][j][d].value();
      }
      else {
        return memo[i][j][d].emplace([&] {
          if (grid[i][j] == 'W') {
            return 0;
          }
          else if (inbound(i + dr[d], j + dc[d])) {
            return (grid[i][j] == 'E' ? 1 : 0) + f(i + dr[d], j + dc[d], d);
          }
          else {
            return static_cast<int>(grid[i][j] == 'E');
          }
        }());
      }
    };

    auto count_enemies = [&](int i, int j) {
      return f(i, j, ll) + f(i, j, rr) + f(i, j, uu) + f(i, j, dd);
    };

    auto solve = [&](int acc = 0) {
      mempool.reset(R, C, 4);
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (grid[r][c] == '0') {
            acc = std::max(acc, count_enemies(r, c));
          }
        }
      }
      return acc;
    };

    return solve();  
  }
};
