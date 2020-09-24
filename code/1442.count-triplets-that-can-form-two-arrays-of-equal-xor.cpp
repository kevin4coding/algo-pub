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
  int countTriplets(vector<int>& arr) {
    arr.insert(std::begin(arr), 0);
    const int n = std::size(arr);

    struct record_t {
      int freq;
      int sum_left_id;
    };

    const auto prefix_xor = [&](std::vector<int> self = {}) {
      self.resize(n, 0);
      for (int i = 0; i < n; ++i) {
        if (i == 0) {
          self[i] = arr[i];
        }
        else {
          self[i] = self[i - 1] ^ arr[i];
        }
      }
      return self;
    }();

    const auto solution = [&, cache = std::unordered_map<int, record_t>{}](int acc = 0) mutable {
      for (int i = 0; i < n; ++i) {
        if (cache.count(prefix_xor[i])) {
          acc += i * cache[prefix_xor[i]].freq - cache[prefix_xor[i]].sum_left_id;
        }
        cache[prefix_xor[i]].freq++;
        cache[prefix_xor[i]].sum_left_id += (i + 1);
      }
      return acc;
    }();

    return arr.erase(std::begin(arr)), solution;
  }
};
