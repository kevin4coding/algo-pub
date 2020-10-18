class Solution {
 public:
  string pushDominoes(string dominoes) {
    const int n = std::size(dominoes);

    std::function<void(int, int)> topple = [&, &D = dominoes](int i, int j) {
      if (i == -1 and D[j] == 'L') {
        for (int k = 0; k <= j; ++k) {
          D[k] = 'L';
        }
      }
      else if (D[i] == 'R' and D[j] == '.') {
        D[j] = 'R';
        D[i + 1] = 'R';
        D[j - 1] = 'R';
        return topple(i + 1, j - 1);
      }
      else if (D[i] == 'R' and D[j] == 'R') {
        if (i + 1 <= j - 1) {
          D[i + 1] = 'R';
          D[j - 1] = 'R';
          return topple(i + 1, j - 1);
        }
      }
      else if ((D[i] == '.' or D[i] == 'L') and D[j] == 'L') {
        if (i + 1 <= j - 1) {
          D[i + 1] = 'L';
          D[j - 1] = 'L';
          return topple(i + 1, j - 1);
        }
      }
      else if (D[i] == 'R' and D[j] == 'L') {
        if (i + 1 < j - 1) {
          D[i + 1] = 'R';
          D[j - 1] = 'L';
          return topple(i + 1, j - 1);
        }
      }
      else if (D[i] == 'L' and D[j] == 'R') {
        return;
      }
      else throw;
    };

    std::function<void(int, std::optional<int>)> fold = [&, &D = dominoes](int i, std::optional<int> prev) {
      if (i == n) {
        return;
      }
      else if (i == 0) {
        return fold(i + 1, D[i] == '.' ? prev : i);
      }
      else if (D[i] == '.') {
        if (i == n - 1 and prev.has_value() and D[prev.value()] == 'R') {
          topple(prev.value(), i);
        }
        return fold(i + 1, prev);
      }
      else if (D[i] == 'R' and (not prev.has_value() or D[prev.value()] == 'L')) {
        return fold(i + 1, i);
      }
      else if (D[i] == 'R' and D[prev.value()] == 'R') {
        topple(prev.value(), i);
        return fold(i + 1, i);
      }
      else if (D[i] == 'L' and not prev.has_value()) {
        topple(-1, i);
        return fold(i + 1, i);
      }
      else if (D[i] == 'L' and D[prev.value()] == 'R' or D[prev.value()] == 'L') {
        topple(prev.value(), i);
        return fold(i + 1, i);
      }
    };
    
    return fold(0, std::optional<int>{}), dominoes;
  }
};
