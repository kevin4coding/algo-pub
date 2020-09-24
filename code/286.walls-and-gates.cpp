class Solution {
 public:
  void wallsAndGates(vector<vector<int>>& rooms) {
    if (std::empty(rooms)) {
      return;
    }
    
    const int R = std::size(rooms);
    const int C = std::size(rooms[0]);
    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};
    
    struct {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::optional<int> D[1000][1000];
    } ST;

    auto init_ST = [&]() {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (rooms[r][c] == 0) {
            ST.Q.emplace_back(std::pair{r, c});
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
          if (inbound(nr, nc) and rooms[nr][nc] != -1 and not D[nr][nc].has_value()) {
            D[nr][nc] = D[r][c].value() + 1;
            Q.emplace_back(nr, nc);
          }
        }
        return bfs();
      }
    };

    const auto solve = [&]() {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (rooms[r][c] == INT_MAX) {
            std::exchange(rooms[r][c], ST.D[r][c].value_or(INT_MAX));
          }
        }
      }
    };

    return init_ST(), bfs(), solve();
  }
};
