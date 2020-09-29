class Solution {
 public:
  int findRotateSteps(string ring, string key) {
    struct {
      mutable std::optional<int> f[105][105]  {};
    } mempool;


    const int n_key = std::size(key);
    const int n_ring = std::size(ring);


    auto inc_ring = [&](int i) {
      return (i + 1) % n_ring;
    };

    auto dec_ring = [&](int i) {
      return (i - 1 + n_ring) % n_ring;
    };

    auto fst_ll = [&](int i, char ch) -> std::pair<std::optional<int>, int> {
      auto [id, acc_steps] = std::pair{std::optional<int>{}, 0};
      for (int k = dec_ring(i); k != i and not id.has_value(); k = dec_ring(k)) {
        acc_steps++;
        if (ring[k] == ch) {
          id = k;
        }
      }
      return std::pair{id, acc_steps};
    };

    auto fst_rr = [&](int i, char ch) -> std::pair<std::optional<int>, int> {
      auto [id, acc_steps] = std::pair{std::optional<int>{}, 0};
      for (int k = inc_ring(i); k!= i and not id.has_value(); k = inc_ring(k)) {
        acc_steps++;
        if (ring[k] == ch) {
          id = k;
        }
      }
      return std::pair{id, acc_steps};
    };
    
    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {          
          if (ring[i] == key[j]) {
            return j == n_key -1 ? 0 : f(i, j + 1);
          }
          else {
            const auto [rr, steps_rr] = fst_rr(i, key[j]);
            const auto [ll, steps_ll] = fst_ll(i, key[j]);
            if (j + 1 == n_key) {
              return std::min(steps_rr, steps_ll);
            }
            else {
              return std::min(steps_ll + f(ll.value(), j + 1) , steps_rr + f(rr.value(), j + 1));
            }
          }
        }());
      }
    };
    
    return f(0, 0) + n_key;
  }
};
