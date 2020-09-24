class Solution {
 public:
  vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
    const int n = std::size(nums);
    
    const auto solution = [&](std::vector<int> self = {}) {
      for (int i = 0; i < n; ++i) {
        self.insert(std::begin(self) + index[i], nums[i]);
      }
      return self;
    }();

    return solution;
  }
};
