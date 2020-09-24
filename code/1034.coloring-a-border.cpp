class Solution {
 public:
  vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
    const int R = std::size(grid);
    const int C = std::size(grid[0]);
    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};


    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    auto atbound = [&](int r, int c) {
      return r == 0 or r == R - 1 or c == 0 or c == C - 1;
    };

    auto check_boundary = [&](int r, int c) {
      return atbound(r, c) or (grid[r + 1][c] != grid[r0][c0]
                               or grid[r - 1][c] != grid[r0][c0]
                               or grid[r][c + 1] != grid[r0][c0]
                               or grid[r][c - 1] != grid[r0][c0]);
    };
        
    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      std::copy(std::begin(grid), std::end(grid), std::back_inserter(self));
      bool vis[50][50] = {};
      std::function<void(int, int)> fold = [&](int r, int c) {
        vis[r][c] = true;
        if (check_boundary(r, c)) {
          self[r][c] = color;
        }
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not vis[nr][nc] and grid[nr][nc] == grid[r0][c0]) {
            fold(nr, nc);
          }
        }
      };

      return fold(r0, c0), self;
    }();

    return solution;
  }
};
