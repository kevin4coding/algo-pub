class Solution {
 public:
  int minCostClimbingStairs(vector<int>& cost) {
    const int n = std::size(cost);
    
    const struct {
      mutable std::optional<int> f[2000];
    } mempool;

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 1 or i == 0) {
            return 0;
          }
          else {
            return std::min(f(i - 1) + cost[i - 1], f(i - 2) + cost[i - 2]);
          }
        }());
      }
    };

    return f(n);
  }
};
