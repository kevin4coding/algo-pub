class Solution {
 public:
  int minDifference(vector<int>& nums) {
    const int n = std::size(nums); 
    
    const auto sorted_nums = [&](std::vector<int> self = {}) {
      std::copy(std::begin(nums), std::end(nums), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    const auto solution = [&] {
      if (std::size(nums) <= 3)
        return 0;
      else
        return std::min({sorted_nums[n - 4] - sorted_nums[0],
                         sorted_nums[n - 3] - sorted_nums[1],
                         sorted_nums[n - 2] - sorted_nums[2],
                         sorted_nums[n - 1] - sorted_nums[3]});
    }();

    return solution;
    
  }
};
