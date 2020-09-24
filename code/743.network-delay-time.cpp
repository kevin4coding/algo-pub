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
  int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    struct state_t {
      mutable std::priority_queue<std::pair<int, int>,
                                  std::vector<std::pair<int, int>>,
                                  std::greater<std::pair<int, int>>> PQ;
      mutable std::optional<int> D[105];
    };

    const auto G = [&](std::vector<std::vector<std::pair<int, int>>> self = {}) {
      self.resize(N + 1);
      for (const auto & e : times) {
        const auto [u, v, w] = std::tuple{e[0], e[1], e[2]};
        self[u].emplace_back(v, w);
      }
      return self;
    }();

    const auto ST = [&](state_t self = {}) {
      self.PQ.emplace(std::pair{0, K});
      std::exchange(self.D[K], 0);
      return self;
    }();

    std::function<void(void)> dijkstra = [&]() {
      if (std::empty(ST.PQ)) {
        return;
      }
      else {
        const auto [D_u, u] = ST.PQ.top();
        ST.PQ.pop();
        // optimize
        if (ST.D[u].has_value() and D_u > ST.D[u].value()) {
          return dijkstra();
        }
        for (const auto [v, w] : G[u]) {
          if (D_u + w < ST.D[v].value_or(INT_MAX)) {
            ST.D[v] = D_u + w;
            ST.PQ.emplace(std::pair{ST.D[v].value(), v});
          }
        }
        return dijkstra();
      }
    };

    const auto solution = [&](std::optional<int> acc = 0) {
      dijkstra();
      for (int u = 1; u <= N and acc.has_value(); ++u) {
        if (ST.D[u].has_value()) {
          acc = std::max(acc.value(), ST.D[u].value());
        }
        else {
          acc.reset();
        }
      }
      return acc.value_or(-1);
    }();

    return solution;
    
  }
};
