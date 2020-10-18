class Solution {
 public:
  int atMostNGivenDigitSet(vector<string>& digits, int n) {
    struct {
      mutable std::optional<int> f[2][10] = {};
    } mempool;

    auto to_digit = [](const std::string ch) -> int {
      return ch[0] - '0';
    };
    
    const auto D = [&](std::vector<int> self = {}) {
      std::transform(std::begin(digits), std::end(digits), std::back_inserter(self), to_digit);
      return self;
    }();

    const auto N = [&](std::vector<int> self = {}) {
      for (auto [x, i] = std::pair{n, 0}; x > 0; x /= 10, i++) {
        self.emplace_back(x % 10);
      }
      std::reverse(std::begin(self), std::end(self));
      return self;
    }();

    const int n_d = std::size(D);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == 0) {
            const int cnt_equal = std::count(std::begin(D), std::end(D), N[j]);
            if (j == 0) {
              return cnt_equal > 0 ? 1 : 0;
            }
            else {
              return cnt_equal > 0 and f(0, j - 1) ? 1 : 0;
            }
          }
          else if (i == 1) {
            const int cnt_less = std::count_if(std::begin(D), std::end(D), [&](auto x) {
              return x < N[j];
            });
            return j == 0 ? cnt_less : f(0, j - 1) * cnt_less + f(1, j - 1) * n_d;
          }
          else throw;
        }());
      }
    };

    const auto K = [&](int acc = 0) {
      for (int i = 1; i < std::size(N); ++i) {
        acc += (int) std::pow(std::size(D), i);
      }
      return acc;
    }();


    return f(0, std::size(N) - 1) + f(1, std::size(N) - 1) + K;
  }
};
