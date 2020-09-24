class Solution {
 public:
  vector<vector<int>> findSubsequences(vector<int>& nums) {
    const int n = std::size(nums);
    
    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      std::function<void(int)> fold = [&, cache = std::vector<int>{}](int i) mutable {
        if (std::size(cache) > 1) {
          self.emplace_back(cache);
        }
        auto used = std::unordered_set<int>{};
        for (int pos = i; pos < n; ++pos) {
          if ((std::empty(cache) or nums[pos] >= cache.back()) and not used.count(nums[pos])) {
            cache.emplace_back(nums[pos]);
            used.emplace(nums[pos]);
            fold(pos + 1);
            cache.pop_back();
          }
        }
      };
      return fold(0), self;
    }();
    
    return solution;
  }
};
