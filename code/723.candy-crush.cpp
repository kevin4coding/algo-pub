class Solution {
 public:
  vector<vector<int>> candyCrush(vector<vector<int>>& board) {
    const int R = std::size(board);
    const int C = std::size(board[0]);
    
    struct state_t {
      mutable std::vector<std::vector<int>> B;
    };

    
    const auto state = state_t {
      .B = board
    };

    auto mark_row = [&](int r) {
      for (auto [i, j] = std::pair{0, 0}; j < C; ++j) {
         if (std::abs(state.B[r][i]) != std::abs(state.B[r][j])) {
           if (j - 1 - i + 1 >= 3) {
             for (int k = i; k < j; ++k) {
               state.B[r][k] = -std::abs(state.B[r][k]);
             }
           }
           i = j;
         }
        else if (j == C - 1 and std::abs(state.B[r][j]) == std::abs(state.B[r][i]) and j - i + 1 >= 3) {
          for (int k = i; k <= j; ++k) {
            state.B[r][k] = -std::abs(state.B[r][k]);
          }
        }
      }
    };

    auto mark_col = [&](int c) {
      for (auto [i, j] = std::pair{0, 0}; j < R; ++j) {
        if (std::abs(state.B[i][c]) != std::abs(state.B[j][c])) {
          if (j - 1 - i + 1 >= 3) {
            for (int k = i; k < j; ++k) {
              state.B[k][c] = -std::abs(state.B[k][c]);
            }
          }
          i = j;
        }
        else if (j == R - 1 and std::abs(state.B[j][c]) == std::abs(state.B[i][c]) and j - i + 1 >= 3) {
          for (int k = i; k <= j; ++k) {
            state.B[k][c] = -std::abs(state.B[k][c]);
          }
        }
      }
    };

    auto drop = [&, DQ = std::deque<int>{}]() mutable {
      auto go = [&](int c) {
        for (auto [i, j] = std::pair{R - 1, R - 1}; j >= 0; --j) {
          if (state.B[j][c] == 0) {
            // do nothing
          }
          else if (state.B[j][c] != 0) {
            state.B[i--][c] = state.B[j][c];
          }
          if (j == 0) {
            for (int k = i; i >= 0; --i) {
              state.B[i][c] = 0;
            }
          }
        }
      };
      for (int c = 0; c < C; ++c) {
        go(c);
      }
    };

    auto crush = [&](int acc = 0) {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (state.B[r][c] < 0) {
            state.B[r][c] = (++acc, 0);
          }
        }
      }
      return acc;
    };

    auto mark = [&]() {
      for (int c = 0; c < C; ++c) {
        mark_col(c);
      }
      for (int r = 0; r < R; ++r) {
        mark_row(r);
      }
    };
    
    std::function<std::vector<std::vector<int>>(void)> eliminate = [&]() -> std::vector<std::vector<int>> {
      if ((mark(), crush()) == 0)
        return state.B;
      else {
        return drop(), eliminate();
      }
    };

    return eliminate();
  }
};
