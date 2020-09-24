class Solution {
 public:
  vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    struct state_t {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::vector<vector<std::optional<int>>> D;
    };

    const int R = std::size(matrix);
    const int C = std::size(matrix[0]);
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    const auto ST = [&](state_t self = {}) {
      self.D.resize(R, std::vector<std::optional<int>>(C));
      
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (matrix[r][c] == 0) {
            self.Q.emplace_back(r, c);
            self.D[r][c].emplace(0);
          }
        }
      }
      return self;
    }();

    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.Q)) {
        return;
      }
      else {
        const auto [r, c] = ST.Q.front();
        ST.Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not ST.D[nr][nc].has_value()) {

            ST.D[nr][nc] = ST.D[r][c].value() + 1;
            ST.Q.emplace_back(nr, nc);
          }
        }
        bfs();
      }
    };

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      bfs();
      self.resize(R, std::vector<int>(C));
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          self[r][c] = ST.D[r][c].value();
        }
      }
      return self;
    }();
    
    return solution;
  }
};
