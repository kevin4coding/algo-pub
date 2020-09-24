class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    using int64 = long;
    
    struct {
      mutable std::set<int> heap = {1};
      mutable std::optional<int> answer = {};
    } ST;

    std::function<int(int)> fold = [&](int i) {
      if (i == n) {
        return *std::begin(ST.heap);
      }
      else {
        const auto min_node = *std::begin(ST.heap);
        ST.heap.erase(min_node);
        for (const auto p : primes) {
          if (int64(p) * int64(min_node) <= INT_MAX) {
            ST.heap.emplace(p * min_node);
          }
        }
        return fold(i + 1);
      }
    };

    return fold(1);
  }
};
