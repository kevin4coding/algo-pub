class Solution {
 public:
  string tictactoe(vector<vector<int>>& moves) {
    const int n = std::size(moves);
    
    const auto struct {
      mutable char board[3][3] = {};
    } state;

    auto check_row = [&, board = std::ref(state.board)](int r) {
      return board[r][0] == board[r][1] and board[r][1] == board[r][2] and (board[r][0] == 'X' or board[r][0] == 'O');
    };

    auto check_col = [&, board = std::ref(state.board)](int c) {
      return board[0][c] == board[1][c] and board[1][c] == board[2][c] and (board[0][c] == 'X' or board[0][c] == 'O');
    };

    auto check_diag = [&, board = std::ref(state.board)]() {
      return board[0][0] == board[1][1] and board[1][1] == board[2][2] and (board[0][0] == 'X' or board[0][0] == 'O');
    };

    auto check_minor_diag = [&, board= std::ref(state.board)]() {
      return board[0][2] == board[1][1] and board[1][1] == board[2][0] and (board[1][1] == 'X' or board[1][1] == 'O');
    };

    std::function<std::string(int)> check = [&, board = std::ref(state.board)](int i) mutable -> std::string {
      if (i == n)
        return n >= 9 ? "Draw" : "Pending";
      else {
        const auto [r, c] = std::pair{moves[i][0], moves[i][1]};
        board[r][c] = (i % 2 == 0) ? 'X' : 'O';
        if (r == c and (check_row(r) or check_col(c) or check_diag() or (r == 1 and check_minor_diag()))) {
          return (i % 2 == 0) ? "A" : "B";
        }
        else if (r + c == 2 and (check_row(r) or check_col(c) or check_minor_diag())) {
          return (i % 2 == 0) ? "A" : "B";
        }
        else if (check_row(r) or check_col(c)) {
          return (i % 2 == 0) ? "A" : "B";
        }
        else {
          return check(i + 1);
        } 
      }
    };
    
    const auto solution = check(0);
    
    return solution;
  }
};
