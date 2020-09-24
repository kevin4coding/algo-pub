class Solution {
 public:
  int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    static const int dr[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    static const int dc[8] = {1, -1, 0, 0, 1, -1, -1, 1};
    const int N = std::size(grid);

    struct {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::optional<int> D[105][105];
    } ST;

    auto init_ST = [&]() {
      if (grid[0][0] == 0) {
        ST.Q.emplace_back(0, 0);
        ST.D[0][0] = 1;
      }
    };

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < N and 0 <= c and c < N;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q) or D[N - 1][N - 1].has_value()) {
        return;
      }
      else {
        const auto [r, c] = Q.front();
        Q.pop_front();
        for (int i = 0; i < 8; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and grid[nr][nc] == 0 and not D[nr][nc].has_value()) {
            D[nr][nc] = D[r][c].value() + 1;
            Q.emplace_back(nr, nc);
          }
        }
        return bfs();
      }
    };

    return init_ST(), bfs(), ST.D[N - 1][N - 1].value_or(-1);
    
  }
};

