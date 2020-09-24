class Solution {
 public:
  vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
    const int R = std::size(mat);
    const int C = std::size(mat[0]);
    
    struct data_t {
      int soldier_cnt;
      int row_id;
    };

    auto sorter = [&](const data_t& d1, const data_t& d2) {
      if (d1.soldier_cnt == d2.soldier_cnt) {
        return d1.row_id < d2.row_id;
      }
      else {
        return d1.soldier_cnt < d2.soldier_cnt;
      }
    };
    
    const auto sorted_data = [&](std::vector<data_t> self = {}) {
      self.resize(R, data_t{});
      for (int r = 0; r < R; ++r) {
        self[r].soldier_cnt = std::accumulate(std::begin(mat[r]), std::end(mat[r]), 0);
        self[r].row_id = r;
      }
      std::sort(std::begin(self), std::end(self), sorter);
      return self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      std::transform(std::begin(sorted_data), std::begin(sorted_data) + k, std::back_inserter(self), [&](const auto &x) {
        return x.row_id;
      });
      return self;
    }();

    return solution;
    
  }
};
