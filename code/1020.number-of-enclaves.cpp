class Solution {
 public:
  int numEnclaves(vector<vector<int>>& A) {
    const int R = std::size(A);
    const int C = std::size(A[0]);
    const int dr[4] = {1, -1, 0, 0};
    const int dc[4] = {0, 0, 1, -1};


    struct cc_t {
      mutable std::vector<std::pair<int, int>> cc;
      mutable bool touch_boundary = false;
    };


    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };

    auto atbound = [&](int r, int c) {
      return r == 0 or r == R - 1 or c == 0 or c == C - 1;
    };

    const auto CC = [&](std::vector<cc_t> self = {}) {
      bool vis[500][500] = {};
      
      std::function<void(int, int)> fold = [&](int r, int c) {
        vis[r][c] = true;
        self.back().cc.emplace_back(std::pair{r, c});
        if (atbound(r, c)) {
          self.back().touch_boundary = true;
        }
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
            self.emplace_back(cc_t{});
            fold(r, c);
          }
        }
      }

      return self;
    }();

    const auto solution = [&](int acc = 0) {
      for (const auto & [cc, touch_boundary] : CC) {
        if (not touch_boundary) {
          acc += std::size(cc);
        }
      }
      return acc;
    }();

    return solution;
    
  }
};


