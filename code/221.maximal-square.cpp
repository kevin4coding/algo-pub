class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    if (std::empty(matrix)) {
      return 0;
    }

    static struct {
      mutable std::optional<int> f[1000][1000];
      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    const int R = std::size(matrix);
    const int C = std::size(matrix[0]);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0 or j == 0) {
            return matrix[i][j] == '1' ? 1 : 0;
          }
          else if (matrix[i][j] == '0') {
            return 0;
          }
          else if (matrix[i][j] == '1') {
            return std::min({f(i - 1, j), f(i, j - 1), f(i - 1, j - 1)}) + 1;
          }
          throw;
        }());
      }
    };

    const auto solution = [&](int acc = 0) {
      mempool.reset(R, C);
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          acc = std::max(acc, f(r, c));
        }
      }
      return acc * acc;
    }();

    return solution;
  }
};
