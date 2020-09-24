class Solution {
 public:
  bool isUgly(int num) {
    const auto primes = std::array{2, 3, 5};

    std::function<bool(int)> fold = [&](int x) {
      if (x == 1) {
        return true;
      }
      else if (x == 0) {
        return false;
      }
      else if (std::min({x % 2, x % 3, x % 5}) > 0) {
        return false;
      }
      else {
        return [&](bool acc = false) {
          for (const auto p : primes) {
            if (x % p == 0) {
              acc |= fold(x / p);
              if (acc) return acc; // prune
            }
          }
          return acc;
        }();
      }
    };

    return fold(num);
  }
};
