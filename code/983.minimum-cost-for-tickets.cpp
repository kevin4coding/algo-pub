class Solution {
 public:
  int mincostTickets(vector<int>& days, vector<int>& costs) {
    static struct {
      mutable std::optional<int> f[365];

      void reset(int r) {
        for (int i = 0; i < r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    const int n = std::size(days);
    const auto pass = std::array{1, 7, 30};

    auto next_lower = [&](int x) {
      auto result = std::optional<int>{};

      std::function<void(int, int)> go = [&](int lo, int hi) {
        const auto mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (days[mid] <= x) {
          result.emplace(mid);
          return go(mid + 1, hi);
        }
        else {
          return go(lo, mid - 1);
        }
      };
      
      return (go(0, n - 1), result);
    };
    
    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return std::min({costs[0], costs[1], costs[2]});
          }
          else {
            return [&](int acc = INT_MAX) {
              for (int k = 0; k < 3; ++k) {
                const auto next = next_lower(days[i] - pass[k]);
                acc = std::min(acc, costs[k] + (next.has_value() ? f(next.value()) : 0));
              }
              return acc;
            }();
          }
        }());
      }
    };
    
    return (mempool.reset(n), f(n - 1));
  }
};
