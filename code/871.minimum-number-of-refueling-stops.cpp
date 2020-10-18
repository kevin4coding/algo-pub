class Solution {
public:
  int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
    if (std::empty(stations)) {
      return startFuel >= target ? 0 : -1;
    }
    
    struct {
      mutable std::optional<int> f[505][505] = {};
    } mempool;

    const int n = std::size(stations);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (j == 0) {
            return startFuel;
          }
          else if (i == 0 and j == 1) {
            return startFuel + (stations[0][0] > startFuel ? 0 : stations[0][1]);
          }
          else if (i + 1 < j) {
            return INT_MIN;
          }
          else {
            return [&](int acc = INT_MIN) {
              if (f(i - 1, j) >= stations[i][0]) {
                acc = std::max(acc, f(i - 1, j));
              }
              if (f(i - 1, j - 1) >= stations[i][0]) {
                acc = std::max(acc, f(i - 1, j - 1) + stations[i][1]);
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](std::optional<int> acc = {}) {
      for (int i = 0; i <= n and not acc.has_value(); ++i) {
        if (f(n - 1, i) >= target) {
          acc.emplace(i);
        }
      }
      return acc.value_or(-1);
    };
    
    return solve();
  }
};

