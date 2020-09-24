class Solution {
 public:
  int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    const int R = std::size(maze);
    const int C = std::size(maze[0]);
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};

    struct state_t {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::optional<int> D[100][100];
    };

    const auto ST = [&](state_t self = {}) {
      self.Q.emplace_back(start[0], start[1]);
      self.D[start[0]][start[1]] = 0;
      return self;
    }();

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };
       
    std::function<std::tuple<int, int, int>(int, int, int, int)> walk = [&](int r, int c, int i, int step) {
      if (not inbound(r + dr[i], c + dc[i]) or maze[r + dr[i]][c + dc[i]] == 1) {
        return std::tuple{r, c, step};
      }
      else {
        return walk(r + dr[i], c + dc[i], i, step + 1);
      }
    };
    
    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.Q)) {
        return;
      }
      else {
        const auto [r, c] = ST.Q.front();
        ST.Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc, w] = walk(r, c, i, 0);
          if (ST.D[r][c].value() + w < ST.D[nr][nc].value_or(INT_MAX)) {
            ST.D[nr][nc] = ST.D[r][c].value() + w;
            ST.Q.emplace_back(nr, nc);
          }
        }
        bfs();
      }
    };

    return bfs(), ST.D[destination[0]][destination[1]].value_or(-1);
  }
};
