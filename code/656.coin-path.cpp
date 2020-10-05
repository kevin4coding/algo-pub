class Solution {
 public:
  vector<int> cheapestJump(vector<int>& A, int B) {

    const int n = std::size(A);
    
    struct {
      mutable std::optional<int> f[1005];
    } mempool;

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == n - 1) {
            return A[i];
          }
          else {
            return [&](int acc = INT_MAX / 2) {
              for (int k = 1; k <= B; ++k) {
                if (i + k < n and A[i + k] != -1) {
                  acc = std::min(acc, A[i] + f(i + k));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](std::vector<int> self = {}) {
      std::function<void(int)> go = [&](int i) {
        if (i == n - 1) {
          self.emplace_back(i + 1);
          return;
        }
        else {
          for (int k = 1; k <= B; ++k) {
            if (i + k < n and A[i] + f(i + k) == f(i)) {
              self.emplace_back(i + 1);
              return go(i + k);
            }
          }
          self.clear();
          return;
        }
      };

      if (f(0) >= INT_MAX / 2) {
        return self;
      }
      else {
        return go(0), self;
      }
    };

    return solve();
  }
};
