class Solution {
 public:
  int maxDistance(vector<vector<int>>& grid) {
    static const int dr[4] = {0, 0, -1, 1};
    static const int dc[4] = {1, -1, 0, 0};
    const int N = std::size(grid);

    struct {
      mutable std::deque<std::pair<int, int>> Q = {};
      mutable std::optional<int> D[105][105] = {};
    } ST;

    auto init_ST = [&]() {
      for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
          if (grid[r][c] == 1) {
            ST.Q.emplace_back(r, c);
            ST.D[r][c] = 0;
          }
        }
      }
    };

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < N and 0 <= c and c < N;
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
          if (inbound(nr, nc) and not D[nr][nc].has_value()) {
            D[nr][nc] = D[r][c].value() + 1;
            Q.emplace_back(nr, nc);
          }
        }
        return bfs();
      }
    };

    const auto solution = [&](int self = INT_MIN) {
      init_ST();
      bfs();
      for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
          if (grid[r][c] == 0) {
            self = std::max(self, ST.D[r][c].value_or(INT_MIN));
          }
        }
      }
      return self == INT_MIN ? -1 : self;
    }();


    return solution;
    
  }
};
