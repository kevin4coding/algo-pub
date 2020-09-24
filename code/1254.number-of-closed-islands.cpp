class Solution {
 public:
  int closedIsland(vector<vector<int>>& grid) {
    const struct {
      mutable std::vector<int> CC = {};
      mutable bool vis[100][100] = {};
    } ST;

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
    
    std::function<void(int, int)> fold = [&](int r, int c) {
      ST.vis[r][c] = true;
      if (atbound(r, c)) {
        std::exchange(ST.CC.back(), 0);
      }
      for (int i = 0; i < 4; ++i) {
        const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
        if (inbound(nr, nc) and grid[nr][nc] == 0 and not ST.vis[nr][nc]) {
          fold(nr, nc);
        }
      }
    };

    const auto solution = [&]() {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (not ST.vis[r][c] and grid[r][c] == 0) {
            ST.CC.emplace_back(1);
            fold(r, c);
          }
        }
      }
      return std::accumulate(std::begin(ST.CC), std::end(ST.CC), 0);
    }();

    return solution;
  }
};
