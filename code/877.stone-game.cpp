class Solution {
 public:
  bool stoneGame(vector<int>& piles) {
    struct {
      mutable std::optional<int> f[505][505] = {};
    } mempool;

    const int n = std::size(piles);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i + 1 == j) {
            return std::max(piles[i], piles[j]) - std::min(piles[i], piles[j]);
          }
          else {
            return std::max(piles[i] - f(i + 1, j), piles[j] - f(i, j - 1));
          }
        }());
      }
    };

    return f(0, n - 1) > 0a;
  }
};
