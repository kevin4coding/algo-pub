namespace {
bool operator<(const unordered_set<char>& a, const unordered_set<char>& b) {
  for (auto elm : a)
    if (b.find(elm) == b.end())
      return false;
  return true;
};
}  // namespace


class Solution {
 public:
  int getMaxRepetitions(string s1, int n1, string s2, int n2) {
    const int l1 = std::size(s1);
    const int l2 = std::size(s2);

    using int64 = long long;
    
    struct {
      mutable std::optional<int64> f[105][32] = {};
    } mempool;

    if (not(unordered_set<char>(s2.begin(), s2.end()) < unordered_set<char>(s1.begin(), s1.end())))
      return 0;

    
    auto single_match_count = [&](int idx) -> int64 {
      int64 acc = 0;
      for (auto [i, j] = std::pair{idx, 0}; j < l2; i = (i + 1) % l1) {
        if (s1[i] == s2[j]) {
          ++j;
        }
        ++acc;
      }
      return acc;
    };

    std::function<int64(int, int)> f = [&, memo = mempool.f](int i, int k) {
      if (memo[i][k].has_value()) {
        return memo[i][k].value();
      }
      else {
        return memo[i][k].emplace([&] {
          if (k == 0) {
            return single_match_count(i);
          }
          else {
            return f(i, k - 1) + f((i + f(i, k - 1)) % l1, k - 1);
          }
        }());
      }
    };

    auto solve = [&](long long acc = 0) {
      std::function<void(int, int)> fill_exponent = [&](int p, int i) {
        if (p < 0) {
          return;
        }
        else if (i + f(i % l1, p) <= n1 * l1) {
          acc += (1 << p);
          return fill_exponent(p, i + f(i % l1, p));
        }
        else {
          return fill_exponent(p - 1, i);
        }
      };
      return fill_exponent(31, 0), acc / n2;
    };

    return solve();
  }
};
