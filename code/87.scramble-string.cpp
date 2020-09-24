template <typename T> std::ostream& operator<<(std::ostream&, const std::set<T>&);
template <typename T> std::ostream& operator<<(std::ostream&, const std::unordered_set<T>&);
template <typename T> std::ostream& operator<<(std::ostream&, const std::vector<T>&);
template <typename K, typename V> std::ostream& operator<<(std::ostream&, const std::unordered_map<K, V>&);
template <typename K, typename V> std::ostream& operator<<(std::ostream&, const std::pair<K, V>&);


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
  bool isScramble(string s1, string s2) {
    const int N = std::size(s1);

    static struct {
      mutable std::optional<int> f[200][200][200];

      void reset(int r, int c, int l) {
        for (int i = 0; i <= r; ++i) {
          for (int j = 0; j <= c; ++j) {
            for (int k = 0; k <= l; ++k) {
              f[i][j][k].reset();
            }
          }
        }
      }
    } mempool;

    std::function<int(int, int, int)> f = [&, memo = mempool.f](int i, int j, int k) {
      if (memo[i][j][k].has_value()) {
        return memo[i][j][k].value();
      }
      else {
        return memo[i][j][k].emplace([&] {
          if (k == 1) {
            return s1[i] == s2[j];
          }

          else {
            return [&](bool acc = false) {
              for (int l = 1; l < k; ++l) {
                acc |= (f(i - l, j - l, k - l) and f(i, j, l))
                    or (f(i - (k - l), j, l) and f(i, j - l, k - l));
              }
              return acc;
            }();
          }
        }());
      }
    };

    return mempool.reset(N - 1, N - 1, N), f(N - 1, N - 1, N);
  }
};
