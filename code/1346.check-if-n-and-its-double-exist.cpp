class Solution {
 public:
  bool checkIfExist(vector<int>& arr) {
    const auto arr_set = [&](std::unordered_set<int> self = {}) {
      std::copy_if(std::begin(arr), std::end(arr), std::inserter(self, std::begin(self)), [](auto &&x) {
        return x != 0;
      });
      return self;
    }();

    const auto solution = [&](bool acc = false) {
      if (std::count(std::begin(arr), std::end(arr), 0) >= 2) {
        return true;
      }
      else {
        for (const auto x : arr_set) {
          acc |= arr_set.count(x * 2);
        }
        return acc;
      }
    }();

    return solution;
  }
};
