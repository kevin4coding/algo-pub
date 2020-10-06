class Solution {
 public:
  int countCornerRectangles(vector<vector<int>>& grid) {
    const int R = std::size(grid);
    const int C = std::size(grid[0]);
    
    const auto ones = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(R, std::vector<int>{});
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (grid[r][c] == 1) {
            self[r].emplace_back(c);
          }
        }
      }
      return self;
    }();

    auto solve = [&](int acc = 0) {
      for (int r1 = 0; r1 < R; ++r1) {
        for (int r2 = r1 + 1; r2 < R; ++r2) {
          int cnt = 0;
          for (const auto k : ones[r2]) {
            if (grid[r1][k] == 1) {
              ++cnt;
            }
          }
          acc += cnt * (cnt - 1) / 2;
        }
      }
      return acc;
    };

    return solve();
  }
};

