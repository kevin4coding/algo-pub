
class Solution {
 public:
  bool makesquare(vector<int>& nums) {
    static const struct {
      mutable std::optional<int> f[1 << 16];
    } mempool;

    
    const auto total_sum = std::accumulate(std::begin(nums), std::end(nums), 0);
    if (total_sum % 4 != 0 or std::size(nums) < 4) {
      return false;
    };

    const int n = std::size(nums);
    const int target = total_sum / 4;

    for (int i = 0; i < (1 << n); ++i) {
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
                if (S & (1 << i)) {
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
    
    return f((1 << n) - 1) == 0;
  }
};
