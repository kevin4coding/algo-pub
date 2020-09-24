
class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    // this is a solution that does not pass OJ test
    static struct {
      mutable std::unordered_map<int, std::optional<int>> f;
      mutable std::optional<int> g[1000005];
    } mempool;


    mempool.f.clear();
    for (int i = 0; i < n; ++i) {
      mempool.g[i].reset();
    }

    std::function<int(int)> f = [&, &memo = mempool.f](int x) {
      if (memo[x].has_value()) {
        return memo[x].value();
      }
      else {
        return memo[x].emplace([&] {
          if (x == 0) {
            return 1;
          }
          else {
            return [&](int acc = INT_MAX) {
              for (const auto p : primes) {
                acc = std::min(acc, f(x / p) * p);
              }
              return acc;
            }();
          }
        }());
      }
    };


    std::function<int(int)> g = [&, memo = mempool.g](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          return i == 0 ? 1 : f(g(i - 1));
        }());
      }
    };

    return g(n - 1);
        
       
  }
};
