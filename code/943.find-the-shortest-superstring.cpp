class Solution {
 public:
  string shortestSuperstring(vector<string>& A) {
    // padding
    A.insert(std::begin(A), std::string{});
    const int n = std::size(A);

    struct {
      mutable std::optional<int> f[1 << 13][13];
    } mempool;

    auto prefix_function = [](const std::string s) {
      const int n = std::size(s);
      
      std::function<int(int)> f = [&, memo = std::vector<std::optional<int>>(n)](int i) mutable {
        if (memo[i].has_value()){ 
          return memo[i].value();
        }
        else {
          return memo[i].emplace([&] {
            if (i == 0) {
              return 0;
            }
            else {
              return [&](std::optional<int> acc = {}) {
                for (int j = f(i - 1); j > 0 and not acc; j = f(j - 1)) {
                  if (s[i] == s[j]) {
                    acc = j + 1;
                  }
                }
                return acc.value_or(s[0] == s[i] ? 1 : 0);
              }();
            }
          }());
        }
      };
      return f;
    };
    
    auto compute_weight = [&](const std::string& s1, const std::string& s2) -> int {
      const int n1 = std::size(s1);
      const int n2 = std::size(s2);
      return prefix_function(s2 + "#" + s1)(n1 + n2);
    };

    const auto G = [&](std::vector<std::vector<std::pair<int, int>>> self = {}) {
      self.resize(n + 1, std::vector<std::pair<int, int>>{});
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          self[i].emplace_back(j, compute_weight(A[i], A[j]));
          self[j].emplace_back(i, compute_weight(A[j], A[i]));
        }
      }
      for (int i = 0; i < n; ++i) {
        self[n].emplace_back(i, 0);
      }
      return self;
    }();

    std::function<int(int, int)> f = [&, memo = mempool.f](int mask, int v) {
      if (memo[mask][v].has_value()) {
        return memo[mask][v].value();
      }
      else {
        return memo[mask][v].emplace([&] {
          if (mask == (1 << n) - 1) {
            return 0;
          }
          else {
            return [&](int acc = INT_MIN) {
              for (const auto [u, w] : G[v]) {
                if ((mask & (1 << u)) == 0) {
                  acc = std::max(acc, w + f(mask | (1 << u), u));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](std::string acc = {}) {
      std::function<void(int, int)> backtrace = [&](int mask, int v) {
        if (mask == (1 << n) - 1) {
          return;
        }
        else {
          for (const auto [u, w] : G[v]) {
            if ((mask & (1 << u)) == 0 and f(mask, v) == f(mask | (1 << u), u) + w) {
              if (mask == 0) {
                acc += A[u];
              }
              else {
                acc += A[u].substr(w);
              }
              return backtrace(mask | (1 << u), u);
            }
          }
        }
      };
      return backtrace(0, 0), acc;
    };
    
    return solve();
  }
};
