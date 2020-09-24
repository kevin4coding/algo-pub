class Solution {
 public:
  int countNegatives(vector<vector<int>>& grid) {
    const int R = std::size(grid);
    const int C = std::size(grid[0]);

    auto bsearch = [&](const std::vector<int>& row) {
      auto result = std::optional<int>{};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (row[mid] < 0) {
          result.emplace(mid);
          go(lo, mid - 1);
        }
        else {
          go(mid + 1, hi);
        }
      };
      return go(0, C - 1), result.value_or(C);
    };

    std::function<int(int)> f = [&](int r) {
      if (r == R) {
        return 0;
      }
      else if (grid[r][0] < 0) {
        return (R - r) * C;
      }
      else {
        return C - 1 - bsearch(grid[r]) + 1 + f(r + 1);
      }
    };

    return f(0);
  }
};
