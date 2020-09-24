#pragma GCC optimize ("O3")
#pragma GCC target ("sse4.1")
static const int _ = []() { return (ios::sync_with_stdio(false), cin.tie(nullptr), 0); }();







class Solution {
 public:
  int numberOfArithmeticSlices(vector<int>& A) {
    const int n = std::size(A);

    using int64 = long;

    struct {
      mutable std::unordered_map<int64, std::optional<int>> f[1000] = {};
    } mempool;

    const auto value_index_map = [&](unordered_map<int, vector<int>>  self =  {}) {
      for (int i = 0; i < n; ++i) {
        self[A[i]].emplace_back(i);
      }
      return self;
    }();

    std::function<int(int, int64)> f = [&, &memo = mempool.f](int i, int64 d) {
      if (memo[i][d].has_value()) {
        return memo[i][d].value();
      }
      else {
        return memo[i][d].emplace([&] {
          if (not value_index_map.count(int64(A[i]) - d)
              or int64(A[i]) - d < INT_MIN
              or int64(A[i]) - d > INT_MAX) {
            return 0;
          }
          else if (i == 1) {
            return A[i] - A[i - 1] == d ? 1 : 0;
          }
          else {
            return [&](int acc = 0) {
              for (const auto j : value_index_map.at(A[i] - d)) {
                if (j < i) {
                  acc += f(j, d) + 1;
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
          acc += f(j, int64(A[i]) - A[j]);
        }
      }
      return acc;
    };


    return solve();
  }
};
