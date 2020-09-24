class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
      const int R = std::size(grid);
      const int C = std::size(grid[0]);
      
      const auto rotated_DQ = [&](std::deque<int> self = {}) {
        for (int r = 0; r < R; ++r) {
          for (int c = 0; c < C; ++c) {
            self.emplace_back(grid[r][c]);
          }
        }
        for (int i = 0; i < k; ++i) {
          self.emplace_front(self.back());
          self.pop_back();
        }
        return self;
      }();


      const auto solution = [&](std::vector<std::vector<int>> self = {}) {
        self.resize(R, std::vector<int>(C, 0));
        for (int r = 0; r < R; ++r) {
          for (int c = 0; c < C; ++c) {
            self[r][c] = rotated_DQ[r * C + c];
          }
        }
        return self;
      }();

      return solution;
    }
};
