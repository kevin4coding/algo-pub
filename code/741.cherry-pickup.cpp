class Solution {
 public:
  int cherryPickup(vector<vector<int>>& grid) {
    const int N = std::size(grid);
    
    struct {
      mutable std::optional<int> f[55][55][55] = {};
    } mempool;

    std::function<int(int, int, int)> f = [&, memo = mempool.f](int r1, int c1, int r2) {
      if (memo[r1][c1][r2].has_value()) {
        return memo[r1][c1][r2].value();
      }
      else {
        return memo[r1][c1][r2].emplace([&] {
          const int c2 = c1 + r1 - r2;
          if (r1 == N - 1 and c1 == N - 1 and r2 == N - 1 and c2 == N - 1) {
            return grid[r1][c1];
          }
          else if (r1 == N or c1 == N or r2 == N or c2 == N or grid[r1][c1] == -1 or grid[r2][c2] == -1) {
            return INT_MIN;
          }
          else {
            const auto curr_score = grid[r1][c1] + ((c2 == c1) ? 0 : grid[r2][c2]);
            const auto next_score = std::max({f(r1 + 1, c1, r2),
                                              f(r1 + 1, c1, r2 + 1),
                                              f(r1, c1 + 1, r2),
                                              f(r1, c1 + 1, r2 + 1)});
            return curr_score + next_score;
          }
        }());
      }
    };

    return std::max(0, f(0, 0, 0));
  }
};
