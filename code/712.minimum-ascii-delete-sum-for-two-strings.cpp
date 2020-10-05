class Solution {
 public:
  int minimumDeleteSum(string s1, string s2) {
    // padding
    s1 = "#" + s1;
    s2 = "#" + s2;
        
    const int n1 = std::size(s1);
    const int n2 = std::size(s2);

    struct {
      mutable std::optional<int> f[1005][1005] = {};
    } mempool;

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0 and j == 0) {
            return 0;
          }
          else if (i == 0 and j != 0) {
            return int(s2[j]) + f(i, j - 1);
          }
          else if (i != 0 and j == 0) {
            return int(s1[i]) + f(i - 1, j);
          }
          else if (s1[i] == s2[j]) {
            return f(i - 1, j - 1);
          }
          else {
            return std::min(int(s1[i]) + f(i - 1, j), int(s2[j]) + f(i, j - 1));
          }
        }());
      }
    };

    return f(n1 - 1, n2 - 1);
  }
};
