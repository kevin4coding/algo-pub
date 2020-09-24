class Solution {
 public:
  vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
    const int R = std::size(board);
    const int C = std::size(board[0]);

    const int dr[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    const int dc[8] = {0, 0, 1, -1, 1, -1, -1, 1};


    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };
    
    auto count_mines = [&](int r, int c) {
      auto acc = 0;
      for (int i = 0; i < 8; ++i) {
        const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
        if (inbound(nr, nc) and board[nr][nc] == 'M') {
          ++acc;
        }
      }
      return acc;
    };
    
    const auto solution = [&](std::vector<std::vector<char>> self = {}) {
      std::copy(std::begin(board), std::end(board), std::back_inserter(self));
      std::function<void(int r, int c)> fold = [&](int r, int c) {
        if (self[r][c] == 'M') {
          std::exchange(self[r][c], 'X');
        }
        else if (self[r][c] == 'E') {
          if (count_mines(r, c) > 0) {
            std::exchange(self[r][c], char('0' + count_mines(r, c)));
          }
          else {
            std::exchange(self[r][c], 'B');
            for (int i = 0; i < 8; ++i) {
              const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
              if (inbound(nr, nc)) {
                fold(nr, nc);
              }
            }
          }
        }
      };

      return fold(click[0], click[1]), self;
      
    }();

    return solution;
  }
};

