template <typename T> std::ostream& operator<<(std::ostream&, const std::set<T>&);
template <typename T> std::ostream& operator<<(std::ostream&, const std::unordered_set<T>&);
template <typename T> std::ostream& operator<<(std::ostream&, const std::vector<T>&);
template <typename K, typename V> std::ostream& operator<<(std::ostream&, const std::unordered_map<K, V>&);
template <typename K, typename V> std::ostream& operator<<(std::ostream&, const std::pair<K, V>&);
template <typename K, typename V> std::ostream& operator<<(std::ostream&, const std::map<K, V>&);


template <typename T>
std::ostream& operator << (std::ostream& os, const std::optional<T>& x) {
  if (x.has_value())
    os << x.value();
  else
    os << "nothing";
  return os;
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& x) {
  os << "(" << x.first << ", " << x.second << ")";
  return os;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::deque<T>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& x) {
  os << "[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : ", ") << *it;
  }
  os << "]";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<vector<T>>& x) {
  os << "\n[";
  for (auto it = begin(x); it != end(x); ++it) {
    os << (it == begin(x) ? "" : "\n ") << *it;
  }
  os << "]";
  return os;
}



#define see(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define trace(x) (cout << see(x) << endl, x)
#define traceX(x) x


class Solution {
 public:
  int minCostII(vector<vector<int>>& costs) {
    if (std::empty(costs)) {
      return 0;
    }

    static struct {
      mutable std::optional<int> f[1000][1000];
      mutable std::optional<int> g[1000][1000];

      void reset(int r, int c) {
        for (int i = 0; i < r; ++i) {
          for (int j = 0; j < c; ++j) {
            f[i][j].reset();
            g[i][j].reset();
          }
        }
      }
    } mempool;
    
    const int n = std::size(costs);
    const int k = std::size(costs[0]);

    std::function<int(int, int)> g = [&, memo = mempool.g](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return costs[i][j];
          }
          else {
            return [&](int acc = INT_MAX) {
              for (int c = 0; c < k; ++c) {
                if (c != j) {
                  acc = std::min(acc, g(i - 1, c) + costs[i][j]);
                }
              }
              return acc;
            }();
          }
        }());
      }
    };
    

    const auto sorted_value_index_group = [&](std::vector<std::map<int, std::unordered_set<int>>> self = {}) {
      const auto S = [&](std::vector<std::set<int>> x = {}) {
        x.resize(n);
        for (int r = 0; r < n; ++r) {
          for (int c = 0; c < k; ++c) {
            x[r].emplace(costs[r][c]);
          }
        }
        return x;
      }();
      
      self.resize(n);
      for (int r = 0; r < n; ++r) {
        const auto fst_min = std::make_optional(*std::begin(S[r]));
        const auto snd_min = std::size(S) == 1 ? std::optional<int>{} : std::make_optional(*std::next(std::begin(S[r])));
        for (int c = 0; c < k; ++c) {
          const auto val = costs[r][c];
          if (val == fst_min.value()) {
            self[r][val].emplace(c);
          }
          else if (snd_min.has_value() and val == snd_min.value()) {
            self[r][val].emplace(c);
          }
        }
      }
      
      return self;
    }();


    cout << see(sorted_value_index_group) << endl;


    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            return costs[i][j];
          }
          else {
            int acc = INT_MAX;
            for (const auto & [val, ids] : sorted_value_index_group[i - 1]) {
              for (const auto k : ids) {
                if (k != j) {
                  acc = std::min(acc, f(i - 1, k) + costs[i][j]);
                }
              }
            }
            return acc;
            // const auto [fst_min_val, fst_min_ids] = sorted_value_index_pair[i - 1][0];
            // const auto [snd_min_val, snd_min_ids] = sorted_value_index_pair[i - 1][1];
            // const auto [fst_min, fst_min_ids] = *sorted_value_index_group.begin();

            
            // if (fst_min_id == j) {
            //   return f(i - 1, snd_min_id) + costs[i][j];
            // }
            // else {
            //   if (snd_min_id != j) {
            //     return std::min(f(i - 1, snd_min_id), f(i - 1, fst_min_id)) + costs[i][j];
            //   }
            //   else {
            //     return f(i - 1, fst_min_id) + costs[i][j];
            //   }
            // }
          }
        }());
      }
    };


    mempool.reset(n, k);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < k; ++j) {
        if (i >= 1) 
          cout << see(i) << see(j) << see(f(i, j)) << see(g(i, j)) << see(costs[i]) << see(sorted_value_index_group[i - 1]) << endl;
      }
    }

    const auto solution = [&](int acc = INT_MAX) {

      for (int i = 0; i < k; ++i) {
        acc = std::min(acc, f(n - 1, i));
      }
      return acc;
    }();

    return solution;
        
  }

};
