class Solution {
 public:
  vector<int> decompressRLElist(vector<int>& nums) {
    const int n = std::size(nums);
    
    const auto solution = [&](std::vector<int> self = {}) {
      for (int i = 0; i < n / 2; ++i) {
        for (int f = 0; f < nums[2 * i]; ++f) {
          self.emplace_back(nums[2 * i + 1]);
        }
      }
      return self;
    }();

    return solution;
  }

};
