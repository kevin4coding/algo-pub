class Solution {
 public:
  int minSwap(vector<int>& A, vector<int>& B) {
    struct {
      mutable std::optional<int> f[1005][2] = {};
    } mempool;

    const int n = std::size(A);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int k) {
      if (memo[i][k].has_value()) {
        return memo[i][k].value();
      }
      else {
        return memo[i][k].emplace([&] {
          if (i == 0) {
            return k == 1 ? 1 : 0;
          }
          else if (k == 1) {
            return [&](int acc = INT_MAX) {
              if (A[i] > A[i - 1] and B[i] > B[i - 1]) {
                acc = std::min(acc, f(i - 1, 1) + 1);
              }
              if (A[i] > B[i - 1] and B[i] > A[i - 1]) {
                acc = std::min(acc, f(i - 1, 0) + 1);
              }
              return acc;
            }();
          }
          else if (k == 0) {
            return [&](int acc = INT_MAX) {
              if (A[i] > A[i - 1] and B[i] > B[i - 1]) {
                acc = std::min(acc, f(i - 1, 0));
              }
              if (A[i] > B[i - 1] and B[i] > A[i - 1]) {
                acc = std::min(acc, f(i - 1, 1));
              }
              return acc;
            }();
          }
          else throw;
        }());
      }
    };

    return std::min(f(n - 1, 1), f(n - 1, 0));
  }
};
