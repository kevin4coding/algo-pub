class Solution {
 public:
  int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
    const struct {
      mutable std::map<std::vector<int>, std::optional<int>> f;
    } mempool;

    const int n = std::size(price);

    auto usable = [&](const std::vector<int> & items, const std::vector<int>& coupon) {
      auto acc = true;
      for (int i = 0; i < n and acc == true; ++i) {
        acc &= (items[i] >= coupon[i]);
      }
      return acc;
    };

    auto use = [&](const std::vector<int> & items, const std::vector<int>& coupon) {
      auto result = std::vector<int>{};
      std::copy(std::begin(items), std::end(items), std::back_inserter(result));
      for (int i = 0; i < n; ++i) {
        result[i] -= coupon[i];
      }
      return result;
    };

    auto buy_regular_price = [&](const std::vector<int>& items) {
      auto acc = int(0);
      for (int i = 0; i < n; ++i) {
        acc += price[i] * items[i];
      }
      return acc;
    };

    std::function<int(std::vector<int>, int)> f = [&](std::vector<int> items, int spending) {
      auto & memo = mempool.f;
      if (memo[items].has_value()) {
        return memo[items].value();
      }
      else {
        return memo[items].emplace([&](int acc = INT_MAX) {
          for (const auto & c : special) {
            if (usable(items, c)) {
              acc = std::min(acc, f(use(items, c), spending + c.back()));
            }
          }
          acc = std::min(acc, spending + buy_regular_price(items));
          return acc;
        }());
      }
    };
    return f(needs, 0);
  }
};
