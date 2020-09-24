class Solution {
 public:
  int climbStairs(int n) {
    static struct {
      mutable std::optional<int> f[100];
      
      void reset(int r) {
        for (int i = 0; i < r;  ++i) {
          f[i].reset();
        }
      }
    } mempool;


    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 1) {
            return 1;
          }
          else if (i == 2) {
            return 2;
          }
          else {
            return f(i - 1) + f(i - 2);
          }
        }());
      }
    };

    return f(n);
  };
};
