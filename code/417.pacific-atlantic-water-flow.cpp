class Solution {
 public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
    // special case
    if (std::empty(matrix)) {
      return {};
    }
    // general case
    const int R = std::size(matrix);
    const int C = std::size(matrix[0]);

    const int pacific = (1 << 0);
    const int atlantic = (1 << 1);


    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    struct node_t {
      int r;
      int c;
      int ocean_id;
    };

    struct state_t {
      mutable std::deque<node_t> Q;
      mutable int visited[150][150];
    };

    auto inboundary = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    const auto ST = [&](state_t self = {}) {
      for (auto [r, c] = std::pair{0, 0}; r < R; ++r) {
        self.Q.emplace_back(node_t{r, c, pacific});
        self.visited[r][c] |= pacific;
      }
      for (auto [r, c] = std::pair{0, 0}; c < C; ++c) {
        self.Q.emplace_back(node_t{r, c, pacific});
        self.visited[r][c] |= pacific;
      }
      for (auto [r, c] = std::pair{0, C - 1}; r < R; ++r) {
        self.Q.emplace_back(node_t{r, c, atlantic});
        self.visited[r][c] |= atlantic;
      }
      for (auto [r, c] = std::pair{R - 1, 0}; c < C; ++c) {
        self.Q.emplace_back(node_t{r, c, atlantic});
        self.visited[r][c] |= atlantic;
      }
      return self;
    }();

    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.Q)) {
        return;
      }
      else {
        const auto [r, c, ocean_id] = ST.Q.front();
        ST.Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::tuple{r + dr[i], c + dc[i]};
          if (inboundary(nr, nc) and not (ST.visited[nr][nc] & ocean_id) and matrix[nr][nc] >= matrix[r][c]) {
            ST.visited[nr][nc] |= ocean_id;
            ST.Q.emplace_back(node_t{nr, nc, ocean_id});
          }
        }
        bfs();
      }
    };

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      bfs();
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (ST.visited[r][c] == (atlantic | pacific)) {
            self.emplace_back(std::vector<int>{r, c});
          }
        }
      }
      return self;
    }();

    return solution;
  }
};
