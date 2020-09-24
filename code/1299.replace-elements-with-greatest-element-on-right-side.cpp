class Solution {
 public:
  vector<int> replaceElements(vector<int>& arr) {
    const int n = std::size(arr);
    
    const auto suffix_max = [&](std::vector<int> self = {}) {
      self.resize(n, 0);
      for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
          self[i] = arr[i];
        }
        else {
          self[i] = std::max(arr[i], self[i + 1]);
        }
      }
      return self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      std::copy(std::begin(suffix_max), std::end(suffix_max), std::back_inserter(self));
      self.erase(std::begin(self));
      self.emplace_back(-1);
      return self;
    }();

    return solution;
    
  }
};
