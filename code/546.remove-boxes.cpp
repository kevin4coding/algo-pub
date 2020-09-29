class Solution {
 public:
  int removeBoxes(vector<int>& boxes) {
    static struct {
      mutable std::optional<int> f[105][105][105];

      void reset(int r, int c, int l) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            for (int k = 0; k <= l; ++k) {
              f[i][j][k].reset();
            }
          }
        }
      }
    } mempool;

    const int n = std::size(boxes);

    std::function<int(int, int, int)> f = [&, memo = mempool.f](int i, int j, int k) {
      if (memo[i][j][k].has_value()) {
        return memo[i][j][k].value();
      }
      else {
        return memo[i][j][k].emplace([&] {
          if (i == j) {
            return (k + 1) * (k + 1);
          }
          else {
            return [&](int acc = INT_MIN) {
              // remove first
              acc = std::max(acc, (k + 1) * (k + 1) + (i + 1 <= j ? f(i + 1, j, 0) : 0));
              // remove middle
              for (int m = i + 1; m <= j; ++m) {
                if (boxes[m] == boxes[i]) {
                  const auto rr = f(m, j, k + 1);
                  const auto ll = (i + 1 <= m - 1) ? f(i + 1, m - 1, 0) : 0;
                  acc = std::max(acc, rr + ll);
                }
              }
              return acc;
            }();
          }
        }());
      }
    };


    mempool.reset(n, n, n);
    return f(0, n - 1, 0);
  }
};

