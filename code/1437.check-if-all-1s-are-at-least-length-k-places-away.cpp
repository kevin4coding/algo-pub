class Solution {
 public:
  bool kLengthApart(vector<int>& nums, int k) {
    const int n = std::size(nums);
    
    const auto solution = [&, DQ = std::deque<int>{}](int acc = true) mutable {
      for (int i = 0; i < n and acc; ++i) {
        DQ.emplace_back(nums[i]);
        while (not std::empty(DQ) and DQ.front() != 1)
          DQ.pop_front();
        if (std::size(DQ) >= 2 and DQ.front() == 1 and DQ.back() == 1) {
          acc &= (std::size(DQ) >= k + 2);
          while (std::size(DQ) > 1) {
            DQ.pop_front();
          }
        }
      }
      return acc;
    }();

    return solution;
  }
};
