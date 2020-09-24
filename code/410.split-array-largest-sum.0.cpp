class Solution {
 public:
  int splitArray(vector<int>& nums, int m) {
    const int n = std::size(nums);
    
    auto splits = [&](int x) {
      int acc_cnt = 0;
      int acc_sum = 0;

      for (int i = 0; i < n; ++i) {
        if (acc_sum + nums[i] > x) {
          ++acc_cnt;
          acc_sum = 0;
        }
        acc_sum += nums[i];
        if (i == n - 1) ++acc_cnt;
      }
      return acc_cnt;
    };


    auto bsearch = [&](std::optional<int> result = {}) {
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (splits(mid) > m) {
          go(mid + 1, hi);
        }
        else {
          result.emplace(mid);
          go(lo, mid - 1);
        }
      };

      const int lo = *std::max_element(std::begin(nums), std::end(nums));
      const int hi = std::accumulate(std::begin(nums), std::end(nums), 0);
      return go(lo, hi), result;
    };

    return bsearch().value();
  }
};
