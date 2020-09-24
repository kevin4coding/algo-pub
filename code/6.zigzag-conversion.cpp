class Solution {
 public:
  string convert(string s, int numRows) {

    const int C = std::size(s);
    const int R = numRows;
    
    const auto mat = [&](std::vector<std::vector<char>> self = {}) {
      self.resize(R, std::vector<char>(C, ' '));
      std::function<void(int, int, int, char)> fmap = [&](int i, int r, int c, char dir) {
        if (i == C) {
          for (int i = 0; i < R; ++i) {
            self[i].resize(c + 1, ' ');
          }
          return;
        }
        else {
          self[r][c] = s[i];
          if (dir == 'd' and r < R - 1) {
            fmap(i + 1, r + 1, c, 'd');
          }
          else if (dir == 'd' and r == R - 1) {
            fmap(i + 1, std::max(0, r - 1), c + 1, 'u');
          }
          else if (dir == 'u' and r > 0) {
            fmap(i + 1, std::max(0, r - 1), c + 1, 'u');
          }
          else if (dir == 'u' and r == 0) {
            fmap(i + 1, std::min(r + 1, R - 1), R == 1 ? c + 1 : c, 'd');
          }
        }
      };

      return fmap(0, 0, 0, 'd'), self;
    }();

    const auto solution = [&](std::string self = {}) {
      
      for (int r = 0; r < R; ++r) {
        std::copy_if(std::begin(mat[r]), std::end(mat[r]), std::back_inserter(self), [&](char ch) {
          return ch != ' ';
        });
      }
      return self;
    }();

    return solution;
  }
};
