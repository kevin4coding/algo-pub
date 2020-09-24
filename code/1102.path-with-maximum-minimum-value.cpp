class Solution {
 public:
  int maximumMinimumPath(vector<vector<int>>& A) {
    const struct {
      mutable std::priority_queue<std::pair<int, std::pair<int, int>>> PQ = {};
      mutable int score = INT_MAX;
      mutable bool vis[100][100] = {};
    } ST;

    const int R = std::size(A);
    const int C = std::size(A[0]);
    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};
    

    auto init_ST = [&]() {
      ST.PQ.emplace(std::pair{A[0][0], std::pair{0, 0}});
      ST.vis[0][0] = true;
    };

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.PQ)) {
        return;
      }
      else {
        const auto [score, u] = ST.PQ.top();
        const auto [r, c] = u;
        ST.PQ.pop();
        ST.score = std::min(ST.score, score);
        if (r == R - 1 and c == C - 1) {
          return;
        }
        else {
          for (int i = 0; i < 4; ++i) {
            const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
            if (inbound(nr, nc) and not ST.vis[nr][nc]) {
              ST.PQ.emplace(std::pair{A[nr][nc], std::pair{nr, nc}});
              ST.vis[nr][nc] = true;
            }
          }
          return bfs();
        }
      }
    };

    return init_ST(), bfs(), ST.score;
  }
};
