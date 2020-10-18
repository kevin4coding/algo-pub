class Solution {
 public:
  int minFallingPathSum(vector<vector<int>>& A) {
    const int R = std::size(A);
    const int C = std::size(A[0]);
    
    struct {
      mutable std::optional<int> f[105][105] = {};
    } mempool;

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return A[i][j];
          }
          else {
            return [&](int acc = INT_MAX) {
              acc = std::min(acc, A[i][j] + f(i - 1, j));
              if (j - 1 >= 0) {
                acc = std::min(acc, A[i][j] + f(i - 1, j - 1));
              }
              if (j + 1 < C) {
                acc = std::min(acc, A[i][j] + f(i - 1, j + 1));
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int acc = INT_MAX) {
      for (int c = 0; c < C; ++c) {
        acc = std::min(acc, f(R - 1, c));
      }
      return acc;
    };

    return solve();
  }
};
