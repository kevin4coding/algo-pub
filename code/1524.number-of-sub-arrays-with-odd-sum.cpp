class Solution {
 public:
  int numOfSubarrays(vector<int>& arr) {

    using int64 = long long;
    
    const struct {
      mutable std::optional<int64> f[100000];
      mutable std::optional<int64> g[100000];
    } mempool;

    const int n = std::size(arr);
    const int64 mod = 1e9 + 7;

    std::function<int64(int)> f, g;
    
    f = [&, memo = std::ref(mempool.f)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return (arr[i] % 2 == 1) ? int64(1) : int64(0);
          }
          else if ((arr[i] % 2) == 1) {
            return g(i - 1) + 1;
          }
          else if ((arr[i] % 2) == 0) {
            return f(i - 1);
          }
          else throw std::domain_error("");
        }());
      }
    };

    g = [&, memo = std::ref(mempool.g)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return ((arr[i] % 2) == 0) ? int64(1) : int64(0);
          }
          else if ((arr[i] % 2) == 0) {
            return g(i - 1) + 1;
          }
          else if ((arr[i] % 2) == 1) {
            return f(i - 1);
          }
          else throw std::domain_error("");
        }());
      }
    };

    const auto solution = [&](int64 acc = 0) {
      for (int i = 0; i < n; ++i) {
        acc = ((acc % mod) + (f(i) % mod)) % mod;
      }
      return acc;
    }();

    return solution;
    
  }
};
