class Solution {
 public:
  int countElements(vector<int>& arr) {
    const auto freq_map = [&](std::unordered_map<int, int> self = {}) {
      for (const auto x : arr) {
        self[x]++;
      }
      return self;
    }();

    const auto solution = [&](int acc = 0) {
      for (const auto x : arr) {
        if (freq_map.count(x + 1)) {
          ++acc;
        }
      }
      return acc;
    }();

    return solution;
  }
};
