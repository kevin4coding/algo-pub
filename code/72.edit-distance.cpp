class Solution {
 public:
  int minDistance(string word1, string word2) {
    static struct {
      mutable std::optional<int> f[1000][1000];

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
          }
        }
      }
    } mempool;

    // padding to prevent a special case.
    word1 = "#" + word1;
    word2 = "#" + word2;

    const int n1 = std::size(word1);
    const int n2 = std::size(word2);

    mempool.reset(n1, n2);
    
    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0 and j == 0) {
            return word1[i] == word2[j] ? 0 : 1;
          }
          else if (i == 0 and j > 0) {
            return word1[i] == word2[j] ? j : 1 + f(i, j - 1);
          }
          else if (i > 0 and j == 0) {
            return word1[i] == word2[j] ? i : 1 + f(i - 1, j);
          }
          else if (word1[i] == word2[j]) {
            return f(i - 1, j - 1);
          }
          else if (word1[i] != word2[j]) {
            return 1 + std::min({f(i, j - 1), f(i - 1, j), f(i - 1, j - 1)});
          }
          throw std::logic_error({});
        }());
      }
    };

    return f(n1 - 1, n2 - 1);
  }
};
