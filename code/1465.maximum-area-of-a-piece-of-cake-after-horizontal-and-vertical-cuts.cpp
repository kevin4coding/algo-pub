class Solution {
 public:
  int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {

    using int64 = long long;

    const int64 mod = 1e9 + 7;
    
    auto make_sorted = [&](const std::vector<int>& arr) {
      auto result = std::vector<int64>{};
      std::copy(std::begin(arr), std::end(arr), std::back_inserter(result));
      std::sort(std::begin(result), std::end(result));
      return result;
    };

    const auto sorted_hcuts = make_sorted(horizontalCuts);
    const auto sorted_vcuts = make_sorted(verticalCuts);

    const auto max_hcut = [&, n = std::size(sorted_hcuts)](int64 acc = LONG_MIN) {
      for (int i = 0; i <= n; ++i) {
        if (i == 0)
          acc = std::max(acc, sorted_hcuts[i]);
        else if (i > 0 and i < n)
          acc = std::max(acc, sorted_hcuts[i] - sorted_hcuts[i - 1]);
        else if (i == n)
          acc = std::max(acc, h - sorted_hcuts[i - 1]);
      }
      return acc;
    }();

    const auto max_vcut = [&, n = std::size(sorted_vcuts)](int64 acc = LONG_MIN) {
      for (int i = 0; i <= n; ++i) {
        if (i == 0)
          acc = std::max(acc, sorted_vcuts[i]);
        else if (i > 0 and i < n)
          acc = std::max(acc, sorted_vcuts[i] - sorted_vcuts[i - 1]);
        else if (i == n)
          acc = std::max(acc, w - sorted_vcuts[i - 1]);
      }
      return acc;
    }();

    const auto solution = (max_vcut % mod) * (max_hcut % mod) % mod;

    return solution;
    
  }
};
