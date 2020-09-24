// to prevent large test case.
const struct {
  mutable std::optional<int> f[1 << 16];
} mempool;

// f(S) = min(g(S - i) + num[i] % target, for i in S and g(S - i) + num[i] <= target)
// Lemma: set S is valid if and only if f(S) == 0. Proof by contradiction would work.

class Solution {
 public:
  bool canPartitionKSubsets(vector<int>& nums, int k) {
    const int sum_nums = std::accumulate(std::begin(nums), std::end(nums), 0);
    const int n = std::size(nums);
    const int target = sum_nums / k;

    // clear cache
    for (int i = 0; i < (1 <<n); ++i) {
      mempool.f[i].reset();
    }

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)](int S) {
      if (memo[S].has_value()) {
        return memo[S].value();
      }
      else {
        return memo[S].emplace([&] {
          if (S == 0) {
            return 0;
          }
          else {
            return [&](int acc = INT_MAX / 2) {
              for (int i = 0; i < n and acc != 0; ++i) {
                if ((1 << i) & S) {
                  const auto S_prev = S ^ (1 << i);
                  if (f(S_prev) + nums[i] <= target and acc != 0) {
                    acc = std::min(acc, (f(S_prev) + nums[i]) % target);
                  }
                }
              }
              return acc;
            }();
          }
        }());
      }
    };
    
    return sum_nums % k == 0 ? f((1 << n) - 1) == 0 : false;
  }
};
