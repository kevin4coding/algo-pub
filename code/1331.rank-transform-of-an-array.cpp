class Solution {
 public:
  vector<int> arrayRankTransform(vector<int>& arr) {

    const auto unique_arr = [&](std::vector<int> self = {}) {
      std::copy(std::begin(arr), std::end(arr), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      self.erase(std::unique(std::begin(self), std::end(self)), std::end(self));
      return self;
    }();

    const auto rank_map = [&](std::unordered_map<int, int> self = {}) {
      for (int i = 0; i < std::size(unique_arr); ++i) {
        self[unique_arr[i]] = i + 1;
      }
      return self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      std::transform(std::begin(arr), std::end(arr), std::back_inserter(self), [&](int x) {
        return rank_map.at(x);
      });
      return self;
    }();

    return solution;
  }
};
