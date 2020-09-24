class Solution {
 public:
  int findLucky(vector<int>& arr) {
    const int n = std::size(arr);
    
    const auto freq_map = [&](std::unordered_map<int, int> self = {}) {
      for (int i = 0; i < n; ++i) {
        self[arr[i]]++;
      }
      return self;
    }();

    const auto lucky_numbers = [&](std::vector<int> self = {}) {
      for (const auto & [val, cnt] : freq_map) {
        if (val == cnt) {
          self.emplace_back(val);
        }
      }
      return self;
    }();

    const auto solution = [&] {
      if (not std::empty(lucky_numbers)) {
        return *std::max_element(std::begin(lucky_numbers), std::end(lucky_numbers));
      }
      else {
        return -1;
      }
    }();

    return solution;
  }
};
