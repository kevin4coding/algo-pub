class Solution {
 public:
  int shortestBridge(vector<vector<int>>& A) {
    const int R = std::size(A);
    const int C = std::size(A[0]);
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};


    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };
    
    const auto CC = [&](std::vector<std::set<std::pair<int, int>>> self = {}) {
      bool vis[100][100] = {};

      std::function<void(int, int)> fold = [&](int r, int c) {
        vis[r][c] = true;
        self.back().emplace(std::pair{r, c});
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not vis[nr][nc] and A[nr][nc] == 1) {
            fold(nr, nc);
          }
        }
      };

      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (not vis[r][c] and A[r][c] == 1) {
            self.emplace_back(std::set<std::pair<int, int>>{});
            fold(r, c);
          }
        }
      }
      return self;
    }();

    const auto & island1 = CC[0];
    const auto & island2 = CC[1];
    

    struct {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::optional<int> D[100][100];
      mutable std::optional<int> D_island2;
    } ST;

    auto init_ST = [&]() {
      for (const auto & [r, c] : island1) {
        ST.Q.emplace_back(std::pair{r, c});
        ST.D[r][c] = 0;
      }
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(ST.Q)) {
        return;
      }
      else {
        const auto [r, c] = ST.Q.front();
        Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not D[nr][nc].has_value()) {
            D[nr][nc] = D[r][c].value() + 1;
            if (not island2.count(std::pair{nr, nc})) {
              Q.emplace_back(std::pair{nr, nc});
            }
            else {
              std::exchange(ST.D_island2, D[nr][nc].value() - 1);
              return;
            }
          }
        }
        return bfs();
      }
    };

    return init_ST(), bfs(), ST.D_island2.value();
  }
};
