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
  int longestSubarray(vector<int>& nums, int limit) {
    const int n = std::size(nums);
    
    const auto solution = [&,
                           DQ_MIN = std::deque<std::pair<int, int>>{},
                           DQ_MAX = std::deque<std::pair<int, int>>{},
                           DQ_WIN = std::deque<std::pair<int, int>>{}](int acc = 0) mutable {
      for (int i = 0; i < n; ++i) {
        while (not std::empty(DQ_MAX) and DQ_MAX.back().second < nums[i]) 
          DQ_MAX.pop_back();
        while (not std::empty(DQ_MIN) and DQ_MIN.back().second > nums[i]) 
          DQ_MIN.pop_back();
        DQ_MAX.emplace_back(std::pair{i, nums[i]});
        DQ_MIN.emplace_back(std::pair{i, nums[i]});
        DQ_WIN.emplace_back(std::pair{i, nums[i]});
        while (DQ_MAX.front().second - DQ_MIN.front().second > limit) {
          if (DQ_WIN.front().second == DQ_MAX.front().second) 
            DQ_MAX.pop_front();
          if (DQ_WIN.front().second == DQ_MIN.front().second) 
            DQ_MIN.pop_front();
          DQ_WIN.pop_front();
        }
        if (not std::empty(DQ_WIN))
          acc = std::max(acc, i - DQ_WIN.front().first + 1);
      }
      return acc;
    }();

    return solution;
  }
};
        
