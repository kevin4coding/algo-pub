class Solution {
 public:
  bool verifyPreorder(vector<int>& preorder) {
    const int n = std::size(preorder);
      
    auto bsearch_inflection = [&](int ll, int rr, int target) {
      auto result = std::optional<int>{};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else {
          if (preorder[mid] > target) {
            go(lo, mid - 1);
          }
          else if (preorder[mid] <= target) {
            if (mid + 1 < n and preorder[mid + 1] > target) {
              result.emplace(mid);
            }
            go(mid + 1, hi);
          }
        }
      };
      return go(ll, rr), result;
    };

    std::function<bool(int, int, int, int)> f = [&](int ll, int rr, int lo, int hi) {
      if (ll > rr or (ll == rr and (lo < preorder[ll] and preorder[ll] < hi))) {
        return true;
      }
      else if (not (lo < preorder[ll] and preorder[ll] < hi)) {
        return false;
      }
      else {
        const auto mid = bsearch_inflection(ll, rr, preorder[ll]);
        if (mid.has_value()) {
          return f(ll + 1, mid.value(), lo, preorder[ll]) and f(mid.value() + 1, rr, preorder[ll], hi);
        }
        else {
          return f(ll + 1, rr, lo, preorder[ll]);
        }
      }
    };
    
    return f(0, n - 1, INT_MIN, INT_MAX);
  }
};
