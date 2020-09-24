class Solution {
 public:
 vector<int> luckyNumbers (vector<vector<int>>& matrix) {
   const int R = std::size(matrix);
   const int C = std::size(matrix[0]);
   
   const auto row_min = [&](std::vector<int> self = {}) {
     self.resize(R, INT_MAX);
     for (int r = 0; r < R; ++r) {
       for (int c = 0; c < C; ++c) {
         self[r] = std::min(matrix[r][c], self[r]);
       }
     }
     return self;
   }();

   const auto col_max = [&](std::vector<int> self = {}) {
     self.resize(C, INT_MIN);
     for (int c = 0; c < C; ++c) {
       for (int r = 0; r < R; ++r) {
         self[c] = std::max(self[c], matrix[r][c]);
       }
     }
     return self;
   }();

   const auto solution = [&](std::vector<int> self = {}) {
     for (int r = 0; r < R; ++r) {
       for (int c = 0; c < C; ++c) {
         if (matrix[r][c] == row_min[r] and matrix[r][c] == col_max[c]) {
           self.emplace_back(matrix[r][c]);
         }
       }
     }
     return self;
   }();

   return solution;   
 }
};
