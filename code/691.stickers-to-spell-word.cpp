class Solution {
 public:
  int minStickers(vector<string>& stickers, string target) {
    struct {
      mutable std::optional<int> f[1 << 16] = {};
    } mempool;

    const int n = std::size(target);

    auto test = [](int mask, int k) { return (mask & (1 << k)) > 0; };

    auto flip = [](int mask, int k) { return (mask ^ (1 << k)); };

    auto apply_sticker = [&](int mask, std::string sticker) {
      for (int i = 0; i < n; ++i) {
        if (test(mask, i)) {
          auto match = std::find(std::begin(sticker), std::end(sticker), target[i]);
          if (match != std::end(sticker)) {
            *match = '_';
            mask = flip(mask, i);
          }
        }
      }
      return mask;
    };   

    std::function<int(int)> f = [&, memo = mempool.f](int mask) {
      if (memo[mask].has_value()) {
        return memo[mask].value();
      }
      else {
        return memo[mask].emplace([&] {
          if (mask == 0) {
            return 0;
          }
          else {
            return [&](int acc = INT_MAX / 2) {
              for (const auto & sticker : stickers) {
                const auto new_mask = apply_sticker(mask, sticker);
                if (new_mask != mask) {
                  acc = std::min(acc, 1 + f(new_mask));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    return f((1 << n) - 1) == INT_MAX / 2 ? -1 : f((1 << n) - 1);   
  }
};
