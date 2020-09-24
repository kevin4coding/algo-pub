template <typename T>
std::ostream& operator << (std::ostream& os, const std::optional<T>& x) {
  if (x.has_value())
    os << x.value();
  else
    os << "nothing";
  return os;
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V> x) {
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
  int findMinFibonacciNumbers(int k) {
    const struct {
      mutable std::optional<int> f[100];
    } mempool;

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0 or i == 1)
            return 1;
          else
            return f(i - 1) + f(i - 2);
        }());
      }
    };

    const auto start_pos = [&](int acc = 0) {
      while (f(acc) <= k and f(acc + 1) <= k) ++acc;
      return acc;
    }();

    const auto solution = [&, remain = k](int acc = 0) mutable {
      std::function<void(int, int)> go = [&](int remain, int i) {
        if (remain == 0 and i < 0) {
          return;
        }
        else if (remain < f(i)) {
          go(remain, i - 1);
        }
        else {
          ++acc, go(remain - f(i), i - 1);
        }
      };
      return go(k, start_pos), acc;
    }();

    return solution;
  }
};
