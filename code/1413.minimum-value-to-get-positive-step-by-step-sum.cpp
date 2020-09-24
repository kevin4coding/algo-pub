class Solution {
 public:
  int minStartValue(vector<int>& nums) {
    const int n = std::size(nums);
    
    const auto prefix_sum = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        if (i == 0) {
          self[i] = nums[i];
        }
        else {
          self[i] = self[i - 1] + nums[i];
        }
      }
      return self;
    }();

    const auto solution = [&]() {
      const auto min_prefix_sum = *std::min_element(std::begin(prefix_sum), std::end(prefix_sum));
      if (min_prefix_sum >= 1) {
        return 1;
      }
      else {
        return 1 - min_prefix_sum;
      }
    }();

    return solution;
  }
};
