class Solution {
 public:
  int deleteAndEarn(vector<int>& nums) {
    if (std::empty(nums)) {
      return 0;
    }
    struct {
      mutable std::optional<int> f[20000] = {};
    } mempool;

    const auto N = [&](std::vector<int> self = {}) {
      std::copy(std::begin(nums), std::end(nums), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      self.erase(std::unique(std::begin(self), std::end(self)), std::end(self));
      return self;
    }();

    const auto scores = [&](std::vector<int> self = {}) {
      self.resize(10005);
      for (const auto x : nums) {
        self[x] += x;
      }
      return self;
    }();

    const int n = std::size(N); 

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return scores[N[i]];
          }
          else if (i == 1) {
            if (N[i] - 1 == N[i - 1]) {
              return std::max(scores[N[i]], scores[N[i - 1]]);
            }
            else {
              return scores[N[i]] + scores[N[i - 1]];
            }
          }
          else {
            if (N[i] - 1 == N[i - 1]) {
              return std::max(scores[N[i]] + f(i - 2), f(i - 1));
            }
            else {
              return f(i - 1) + scores[N[i]];
            }
          }
        }());
      }
    };

    return f(n - 1);   
  }
};
