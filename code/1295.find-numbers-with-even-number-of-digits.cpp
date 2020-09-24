class Solution {
 public:
  int findNumbers(vector<int>& nums) {
    const int n = std::size(nums);
    
    const auto solution = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        acc += ((int)std::log10(nums[i]) + 1) % 2 == 0;
      }
      return acc;
    }();

    return solution;
  }
};
