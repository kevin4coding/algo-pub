class Solution {
 public:
  void solve(vector<vector<char>>& board) {
    if (std::empty(board)) {
      return;
    }
    
    const int R = std::size(board);
    const int C = std::size(board[0]);
    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};

    auto is_valid_cc = [&](const std::vector<std::pair<int, int>>& x) {
      return 0 == std::count_if(std::begin(x), std::end(x), [&](auto && x) {
        return x.first == 0 or x.first == R - 1 or x.second == 0 or x.second == C - 1;
      });
    };

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };
    
    const auto cc = [&](std::vector<std::vector<std::pair<int, int>>> self = {}) {
      auto visited = std::vector<std::vector<bool>>(R, std::vector<bool>(C, false)); // mutable state
          
      std::function<void(int, int)> fold = [&](int r, int c) mutable {
        visited[r][c] = true;
        self.back().emplace_back(r, c);
        for (int i = 0; i < 4; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (inbound(nr, nc) and not visited[nr][nc] and board[nr][nc] == 'O') {
            fold(nr, nc);
          }
        }
      };

      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (board[r][c] == 'O' and not visited[r][c]) {
            self.emplace_back(std::vector<std::pair<int, int>>{});
            fold(r, c);
          }
        }
      }
      return self;
    }();

    auto modify = [&]() {
      for (const auto & c : cc) {
        if (is_valid_cc(c)) {
          for (const auto [r, c] : c) {
            std::exchange(board[r][c], 'X');
          }
        }
      }
    };

    modify();
  }
};
