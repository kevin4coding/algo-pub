class Solution {
 public:
  vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
    const int R = std::size(mat);
    const int C = std::size(mat[0]);
    
    auto sorted_diag = [&](int r, int c) {
      c -= std::min(r, c);
      r -= std::min(r, c);
      auto acc = std::vector<int>{};
      for (int i = 0; i < std::min(R - r, C - c); ++i) {
        acc.emplace_back(mat[r + i][c + i]);
      }
      std::sort(std::begin(acc), std::end(acc));
      return acc;
    };
    
    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(R, std::vector<int>(C, 0));
      
      auto set_diag = [&](int r, int c) {
        c -= std::min(r, c);
        r -= std::min(r, c);
        const auto new_diag = sorted_diag(r, c);
        for (int i = 0; i < std::min(R - r, C - c); ++i) {
          self[r + i][c + i] = new_diag[i];
        }
      };
      
      for (int c = 0; c < C; ++c) {
        set_diag(0, c);
      }
      for (int r = 1; r < R; ++r) {
        set_diag(r, 0);
      }

      return self;
    }();

    return solution;
  }
};
