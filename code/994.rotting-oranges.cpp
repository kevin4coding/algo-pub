class Solution {
 public:
  int orangesRotting(vector<vector<int>>& grid) {
    static const int dr[4] = {0, 0, 1, -1};
    static const int dc[4] = {1, -1, 0, 0};
    const int R = std::size(grid);
    const int C = std::size(grid[0]);


    struct {
      mutable std::deque<std::pair<int, int>> Q = {};
      mutable std::optional<int> D[15][15] = {};
    } ST;

    auto init_ST = [&]() {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (grid[r][c] == 2) {
            ST.Q.emplace_back(r, c);
            ST.D[r][c] = 0;
          }
        }
      }
    };

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q)) {
        return; 
      }
      else {
        const auto [r, c] = Q.front();
        Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and grid[nr][nc] == 1 and not D[nr][nc].has_value()) {
            D[nr][nc] = D[r][c].value() + 1;
            Q.emplace_back(nr, nc);
          }
        }
        return bfs();
      }
    };

    const auto solution = [&](std::optional<int> acc = 0) {
      init_ST();
      bfs();
      for (int r = 0; r < R and acc.has_value(); ++r) {
        for (int c = 0; c < C and acc.has_value(); ++c) {
          if ((grid[r][c] == 1 or grid[r][c] == 2)and ST.D[r][c].has_value()) {
            acc = std::max(acc.value(), ST.D[r][c].value());
          }
          else if (grid[r][c] == 1 and not ST.D[r][c].has_value()) {
            acc.reset();
          }
        }
      }
      return acc.value_or(-1);
    }();

    return solution;
    
  }
};
