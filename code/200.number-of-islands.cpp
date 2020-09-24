class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    if (std::empty(grid)) {
      return 0;
    }
    const auto R = std::size(grid);
    const auto C = std::size(grid[0]);

    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};


    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    const auto solution = [&](int acc = 0) {
      auto visited = std::vector<std::vector<bool>>(R, std::vector<bool>(C, false));

      std::function<void(int, int)> fold = [&](int r, int c) {
        visited[r][c] = true;
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not visited[nr][nc] and grid[nr][nc] == '1') {
            fold(nr, nc);
          }
        }
      };

      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (not visited[r][c] and grid[r][c] == '1') {
            ++acc;
            fold(r, c);
          }
        }
      }

      return acc;
    }();

    return solution;

    
  }
};
