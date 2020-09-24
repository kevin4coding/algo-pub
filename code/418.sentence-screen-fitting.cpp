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
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    const int n = std::size(sentence);
    
    auto fill = [&, memo = std::vector<std::optional<std::pair<int, int>>>(n)](int i) mutable {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          struct {
            mutable int sid = 0;
            mutable int cid = 0;
            mutable int acc_cnt = 0;
          } ST;

          ST.sid = i;
          for (int i = 0; ; i = i % n) {
            if (cols - ST.cid + 1 < std::size(sentence[ST.sid]) + 1) {
              break;
            }
            else {
              ST.cid += std::size(sentence[ST.sid]) + 1;
              ST.sid = (ST.sid + 1) % n;
              ++ST.acc_cnt;
            }
          }
          return std::pair{ST.acc_cnt, ST.sid};
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      for (auto [i, sid] = std::pair{0, 0}; i < rows; ++i) {
        auto [filled, next] = fill(sid);
        sid = next;
        acc += filled;
      }
      return acc / n;
    };
    
    return solve();
  }
};
