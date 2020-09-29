class Solution {
 public:
  int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
    const int N = std::size(flights);
    const int K = std::size(days[0]);
    
    struct {
      mutable std::optional<int> f[105][105] = {};
    } mempool;

    std::function<int(int, int)> f = [&, memo = mempool.f](int k, int i) {
      if (memo[k][i].has_value()) {
        return memo[k][i].value();
      }
      else {
        return memo[k][i].emplace([&] {
          if (k == K) {
            return 0;
          }
          else {
            return [&](int acc = INT_MIN) {
              // stay
              acc = std::max(acc, days[i][k] + f(k + 1, i));
              // fly
              for (int j = 0; j < N; ++j) {
                if (flights[i][j] == 1)  {
                  acc = std::max(acc, days[j][k] + f(k + 1, j));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };
    
    return f(0, 0);
  }
};
