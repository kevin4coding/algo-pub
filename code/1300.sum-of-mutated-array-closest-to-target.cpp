class Solution {
 public:
  int findBestValue(vector<int>& arr, int target) {
    const int n = std::size(arr);

    auto f = [&](int truncate) {
      int acc = 0;
      for (int i = 0; i < n; ++i) {
        acc += std::min(truncate, arr[i]);
      }
      return acc;
    };

    auto binary_search = [&](int ll, int rr) {
      auto result = std::optional<int>{};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        const int f_mid = f(mid);
        if (lo > hi) {
          return;
        }
        else if (f_mid >= target) {
          result.emplace(mid);
          go(lo, mid - 1);
        }
        else if (f_mid < target) {
          go(mid + 1, hi);
        }
      };
      return go(ll, rr), result;
    };

    const auto solution = [&](int self = {}) {
      const auto candidate = binary_search(1, *std::max_element(std::begin(arr), std::end(arr)));
      if (not candidate.has_value())
        return *std::max_element(std::begin(arr), std::end(arr));
      else if (std::abs(target - f(candidate.value() - 1)) <= std::abs(target - f(candidate.value())))
        return candidate.value() - 1;
      else
        return candidate.value();
    }();

    return solution;
  }
};
