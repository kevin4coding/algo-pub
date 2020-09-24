class Solution {
 public:
  int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
    auto sorter = [](const std::pair<int, int>& p1, const std::pair<int, int>&p2) {
      return p1.second < p2.second;
    };
    
    const auto freq_map = [&](std::unordered_map<int, int> self = {}) {
      for (const auto x : arr) 
        self[x]++;
      return self;
    }();

    const auto sorted_map = [&](std::vector<std::pair<int, int>> self = {}) {
      std::copy(std::begin(freq_map), std::end(freq_map), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self), sorter);
      return self;
    }();

    const auto solution = [&, cache = 0, id = 0]() mutable {
      for (const auto [val, cnt] : sorted_map) {
        if (cache + cnt <= k) {
          cache += cnt;
          ++id;
        }
      }
      return std::size(sorted_map) - id;
    }();

    return solution;
  }
};
