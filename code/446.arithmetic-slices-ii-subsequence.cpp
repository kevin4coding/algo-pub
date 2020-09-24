using int64 = long;

static struct {
  mutable std::unordered_map<int64, int> f[1000] = {};
} mempool;


class Solution {
 public:
  int numberOfArithmeticSlices(vector<int>& A) {
    const int n = std::size(A);

    auto f_eval = [&, &f = mempool.f]() {
      int acc_sum = 0;

      for (int i = 0; i < n; ++i) {
        mempool.f[i].clear();
      }
      
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
          const int64 d = int64(A[i]) - A[j];
          f[i][d] = f[i][d] + f[j][d] + 1;
          acc_sum += f[j][d] + 1;
        }
      }

      return acc_sum  - n * (n - 1) / 2;
    };

    return f_eval();
  }
};
