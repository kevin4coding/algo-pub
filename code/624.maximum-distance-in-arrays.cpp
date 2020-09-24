class Solution {
 public:
  int maxDistance(vector<vector<int>>& arrays) {
    const int n = std::size(arrays);

    const auto prefix_min = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        if (i == 0) {
          self[i] = arrays[i].front();
        }
        else {
          self[i] = std::min(self[i - 1], arrays[i][0]); 
        }
      }
      return self;
    }();

    const auto prefix_max = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        if (i == 0) {
          self[i] = arrays[i].back();
        }
        else {
          self[i] = std::max(self[i - 1], arrays[i].back());
        }
      }
      return self;
    }();

    const auto suffix_min = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
          self[i] = arrays[i].front();
        }
        else {
          self[i] = std::min(self[i + 1], arrays[i].front());
        }
      }
      return self;
    }();

    const auto suffix_max = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
          self[i] = arrays[i].back();
        }
        else {
          self[i] = std::max(self[i + 1], arrays[i].back());
        }
      }
      return self;
    }();


    const auto solution = [&](int acc = INT_MIN) {
      for (int i = 0; i < n; ++i) {
        const auto [cur_min, cur_max] = std::pair{arrays[i].front(), arrays[i].back()};
        if (i == 0) {
          acc = std::max({acc,
                          std::abs(cur_min - suffix_max[i + 1]),
                          std::abs(cur_max - suffix_min[i + 1])});
        }
        else if (i > 0 and i < n - 1) {
          acc = std::max({acc,
                          std::abs(cur_min - suffix_max[i + 1]),
                          std::abs(cur_max - suffix_min[i + 1]),
                          std::abs(cur_min - prefix_max[i - 1]),
                          std::abs(cur_max - prefix_min[i - 1])});
        }
        else if (i == n - 1) {
          acc = std::max({acc,
                          std::abs(cur_min - prefix_max[i - 1]),
                          std::abs(cur_max - prefix_min[i - 1])});
        }
      }
      return acc;
    }();

    return solution;
  }
};
