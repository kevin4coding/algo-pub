class Solution {
 public:
  int minSetSize(vector<int>& arr) {

    const int n = std::size(arr);

    auto sorter = [&](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
      return p1.first > p2.first;
    };
    
    const auto freq_map = [&](std::unordered_map<int, int> self = {}) {
      for (const auto x : arr) {
        self[x]++;
      }
      return self;
    }();

    const auto inverse_freq_map = [&](std::vector<std::pair<int, int>> self = {}) {
      for (const auto [key, val] : freq_map) {
        self.emplace_back(std::pair{val, key});
      }
      std::sort(std::begin(self), std::end(self), sorter);
      return self;
    }();

    const auto solution = [&](int acc = 0) {
      for (auto [i, remain] = std::pair{0, n}; i < std::size(inverse_freq_map) and remain > n / 2; ++i) {
        const auto [freq, val] = inverse_freq_map[i];
        remain -= freq;
        ++acc;
      }
      return acc;
    }();


    return solution;
    
  }
};
