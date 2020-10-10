class Solution {
 public:
  double largestSumOfAverages(vector<int>& A, int K) {
    struct {
      mutable std::optional<double> f[105][105] = {};
    } mempool;

    const int n = std::size(A);
    
    const auto prefix_sum = [&, self = std::vector<int>(n, 0)]() mutable {
      for (int i = 0; i < n; ++i) {
        self[i] = i == 0 ? A[i] : self[i - 1] + A[i];
      }
      return self;
    }();

    auto RSQ = [&](int i, int j) -> double {
      return prefix_sum[j] - (i == 0 ? 0 : prefix_sum[i - 1]);
    };

    std::function<double(int, int)> f = [&, memo = mempool.f](int i, int k) {
      if (memo[i][k].has_value()) {
        return memo[i][k].value();
      }
      else {
        return memo[i][k].emplace([&] {
          if (i + 1 == k) {
            return RSQ(0, i);
          }
          else if (k == 1) {
            return RSQ(0, i) / (i + 1);
          }
          else {
            return [&](double acc = INT_MIN) {
              for (int j = i; j - 1 + 1 >= k - 1; --j) {
                acc = std::max(acc, f(j - 1, k - 1) + (RSQ(j, i) / (i - j + 1)));
              }
              return acc;
            }();
          }
        }());
      }
    };
    
    return f(n - 1, K);
  }
};
