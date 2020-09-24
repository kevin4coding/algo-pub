class Solution {
 public:
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    const int R = std::size(maze);
    const int C = std::size(maze[0]);
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    
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

    std::function<std::tuple<int, int>(int, int, int, int)> walk = [&](int r, int c, int dr, int dc) {
      if (not inbound(r + dr, c + dc) or maze[r + dr][c + dc] == 1) {
        return std::tuple{r, c};
      }
      else {
        return walk(r + dr, c + dc, dr, dc);
      }
    };

    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.Q) or ST.D[destination[0]][destination[1]].has_value()) {
        return;
      }
      else {
        const auto [r, c] = ST.Q.front();
        ST.Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = walk(r, c, dr[i], dc[i]);
          if (not ST.D[nr][nc].has_value()) {
            ST.D[nr][nc] = ST.D[r][c].value() + 1;
            ST.Q.emplace_back(nr, nc);
          }
        }
        bfs();
      }
    };

    return bfs(), ST.D[destination[0]][destination[1]].has_value();
  }
};

