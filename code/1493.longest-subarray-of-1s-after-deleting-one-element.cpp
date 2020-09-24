class Solution {
 public:
  int longestSubarray(vector<int>& nums) {
    const int n = std::size(nums); 
    
    const auto solution = [&, DQ = std::deque<int>{}, zero_cnt = 0](int acc = 0) mutable {
      for (int i = 0; i < n; ++i) {
        if (nums[i] == 0 and zero_cnt == 1) {
          acc = std::max(acc, (int)std::size(DQ) - 1);
          while (not std::empty(DQ) and zero_cnt == 1) {
            zero_cnt -= DQ.front() == 0;
            DQ.pop_front();
          }
          if (not std::empty(DQ)) {
            DQ.emplace_back(nums[i]);
            zero_cnt++;
          }
        }
        else if (nums[i] == 0 and zero_cnt == 0) {
          if (not std::empty(DQ)) {
            zero_cnt++;
            DQ.emplace_back(nums[i]);
          }
        }
        else if (nums[i] == 1) {
          DQ.emplace_back(nums[i]);
          acc = std::max(acc, (int) std::size(DQ) - (zero_cnt == 1));
        }
      }
      return acc == n ? acc - 1 : acc;
    }();


    return solution;
  }
};
