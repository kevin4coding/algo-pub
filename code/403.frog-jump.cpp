class Solution {
 public:
  bool canCross(vector<int>& stones) {
    struct {
      mutable std::unordered_map<int, std::unordered_map<int, std::optional<bool>>> f = {};
    } mempool;

    const auto stone_set = std::unordered_set<int>(std::begin(stones), std::end(stones));

    const auto target = stones.back();

    std::function<bool(int, int)> f = [&, &memo = mempool.f](int x, int y) {
      if (memo[x][y].has_value()) {
        return memo[x][y].value();
      }
      else {
        return memo[x][y].emplace([&] {
          if (x == 1 and y == 1) {
            return true;
          }
          else if (y <= 1 or not stone_set.count(x)) {
            return false;
          }
          else {
            return f(x - y, y) or f(x - y, y + 1) or f(x - y, y - 1);
          }
        }());
      }
    };

    auto solve = [&](bool acc = false) {
      for (int i = 1; i <= 1001 and not acc; ++i) {
        acc |= f(target, i);
      }
      return acc;
    };

    return solve();
  }
};
