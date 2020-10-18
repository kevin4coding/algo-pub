class Solution {
 public:
  int tallestBillboard(vector<int>& rods) {
    const int n = std::size(rods);
    
    struct {
      mutable std::optional<int> f[22][5005];
    } mempool;

    std::function<int(int, int)> f = [&, &memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == n) {
            return j == 0 ? 0 : INT_MIN;
          }
          else {
            return std::max({f(i + 1, j), f(i + 1, j + rods[i]), f(i + 1, std::abs(j - rods[i])) + std::min(j, rods[i])});
          }
        }());
      }
    };

    return f(0, 0) < 0 ? 0 : f(0, 0);
  }
};
