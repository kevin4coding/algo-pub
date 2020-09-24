class Solution {
 public:
  int nthUglyNumber(int n) {
    static struct {
      mutable std::unordered_map<int, std::optional<int>> f = {};
      mutable std::optional<int> g[2000] = {};
    } mempool;

    // no need to clear mempool because ugly number is a pure function.
    // not really sure how it works.. 
    // assume x is an ugly number
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
            return std::min({f(x / 3) * 3, f(x / 2) * 2, f(x / 5) * 5});
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

// vision
// xyab32do
