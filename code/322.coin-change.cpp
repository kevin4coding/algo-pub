class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    static struct {
      mutable std::optional<int> f[10000] = {};

      void reset(int r) {
        for (int i = 0; i < r; ++i) {
          f[i].reset();
        }
      }
      
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int s) {
      if (memo[s].has_value()) {
        return memo[s].value();
      }
      else {
        return memo[s].emplace([&] {
          if (s == 0) {
            return 0;
          }
          else {
            return [&](int acc = INT_MAX / 2) {
              for (const auto coin : coins) {
                if (s - coin >= 0) {
                  acc = std::min(acc, 1 + f(s - coin));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    mempool.reset(amount + 1);
    
    return f(amount) == INT_MAX / 2 ? -1 : f(amount);
  }
};
