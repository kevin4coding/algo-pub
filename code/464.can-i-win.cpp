class Solution {
 public:
  bool canIWin(int maxChoosableInteger, int desiredTotal) {
    static struct {
      mutable std::optional<bool> f[1 << 21] = {};

      void reset(int r) {
        for (int i = 0; i <= r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    const int n = maxChoosableInteger;
        
    std::function<bool(int, int)> f = [&, memo = mempool.f](int S, int x) {
      if (memo[S].has_value()) {
        return memo[S].value();
      }
      else {
        return memo[S].emplace([&] {
          if (S == ((1 << n + 1) - 1)) {
            return false;
          }
          bool acc = false;
          for (int i = n; i > 0 and acc == false; --i) {
            if ((S & (1 << i)) == 0) {
              acc |= (i >= x) or (not f(S | (1 << i), x - i));
            }
          }
          return acc;      
        }());
      }
    };


    auto solve = [&]() {
      if (n * (n + 1) / 2 < desiredTotal) {
        return false;
      }
      else {
        mempool.reset(1 << (n + 1));
        return f(0, desiredTotal);
      }
    };

    return solve();
  }
};


