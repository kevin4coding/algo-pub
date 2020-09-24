class Solution {
 public:
  int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
    const int n1 = std::size(arr1);
    const int n2 = std::size(arr2);
    
    const auto sorted_arr2 = [&](std::vector<int> self = {}) {
      std::copy(std::begin(arr2), std::end(arr2), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    auto bsearch_hi = [&](int target) {
      auto result = std::optional<int>{};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          if (result.has_value() and sorted_arr2[result.value()] < target) {
            result.reset();
          }
          return;
        }
        else if (sorted_arr2[mid] <= target + d) {
          result.emplace(mid);
          go(mid + 1, hi);
        }
        else {
          go(lo, mid - 1);
        }
      };
      return go(0, n2 - 1), result;
    };

    auto bsearch_lo = [&](int target) {
      auto result = std::optional<int>{};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          if (result.has_value() and sorted_arr2[result.value()] > target) {
            result.reset();
          }
          return;
        }
        else if (sorted_arr2[mid] >= target - d) {
          result.emplace(mid);
          go(lo, mid - 1);
        }
        else {
          go(mid + 1, hi);
        }
      };
      return go(0, n2 - 1), result;
    };
    
    const auto solution = [&](int acc = 0) {
      for (int i = 0; i < n1; ++i) {
        const auto [l, r] = std::pair{bsearch_lo(arr1[i]), bsearch_hi(arr1[i])};
        if (not l.has_value() and not r.has_value()) {
          ++acc;
        }
      }
      return acc;
    }();

    return solution;
  }
};
