class Solution {
 public:
  int oddCells(int n, int m, vector<vector<int>>& indices) {
    using int64 = long long;
      
    const int64 row_flag = [&](int64 self = 0) {
      for (const auto & index : indices) {
        self ^= (1ULL << index[0]);
      }
      return self;
    }();

    const int64 col_flag = [&](int64 self = 0) {
      for (const auto & index : indices) {
        self ^= (1ULL << index[1]);
      }
      return self;
    }();

    const auto solution = [&] {
      const int odd_rows = __builtin_popcountll(row_flag);
      const int odd_cols = __builtin_popcountll(col_flag);
      return odd_rows * m + odd_cols * n - 2 * odd_rows * odd_cols;
    }();

    return solution;
  }
};
