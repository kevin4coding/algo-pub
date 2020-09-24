/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
 public:
  int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
    const auto dim = binaryMatrix.dimensions();
    const auto R = dim[0];
    const auto C = dim[1];
    
    auto check_col = [&](int c) {
      auto acc = false;
      for (int r = 0; r < R and not acc; ++r) {
        acc |= (binaryMatrix.get(r, c) == 1);
      }
      return acc;
    };

    auto bsearch = [&]() {
      std::optional<int> result = {};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (check_col(mid) == true) {
          result.emplace(mid);
          go(lo, mid - 1);
        }
        else {
          go(mid + 1, hi);
        }
      };
      return go(0, C - 1), result;
    };


    const auto solution = bsearch().value_or(-1);


    return solution;
  }
};
