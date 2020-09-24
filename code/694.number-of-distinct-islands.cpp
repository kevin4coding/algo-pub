class Solution {
 public:
  int numDistinctIslands(vector<vector<int>>& grid) {
    const int R = std::size(grid);
    const int C = std::size(grid[0]);
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    auto normalize = [&](std::vector<std::vector<int>> arr) {
      const auto maxr = [&](int acc = INT_MIN) {
        for (const auto& e : arr) {
          acc = std::max(acc, e[0]);
        }
        return acc;
      }();
      const auto maxc = [&](int acc = INT_MIN) {
        for (const auto&e : arr) {
          acc = std::max(acc, e[1]);
        }
        return acc;
      }();

      for (auto & e : arr) {
        std::exchange(e[0], e[0] - maxr);
        std::exchange(e[1], e[1] - maxc);
      }
      return arr;
    };
    
    const auto CC = [&](std::vector<std::vector<std::vector<int>>> self = {}) {
      bool visited[50][50] = {};
      std::function<void(int, int)> fold = [&](int r, int c) {
        visited[r][c] = true;
        self.back().emplace_back(std::vector<int>{r, c});
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not visited[nr][nc] and grid[nr][nc] == 1) {
            fold(nr, nc);
          }
        }
      };

      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (not visited[r][c] and grid[r][c] == 1) {
            self.emplace_back(std::vector<std::vector<int>>{});
            fold(r, c);
          }
        }
      }
      return self;
    }();

    const auto normalized_CC = [&](std::set<std::vector<std::vector<int>>> self = {}) {
      for (const auto & c : CC) {
        self.emplace(normalize(c));
      }
      return self;
    }();

    return std::size(normalized_CC);
        
  }
};
