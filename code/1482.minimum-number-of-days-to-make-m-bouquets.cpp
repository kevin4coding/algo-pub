class Solution {
 public:
  int minDays(vector<int>& bloomDay, int m, int k) {
    const int n = std::size(bloomDay);
    
    auto check = [&, DQ = std::deque<int>{}, flowers = std::vector<int>(n, 0)](int day) mutable {
      DQ.clear();
      auto acc = int{0};
      for (int i = 0; i < n; ++i) {
        flowers[i] = static_cast<int>(bloomDay[i] <= day);
      }
      for (int i = 0; i < n and acc < m; ++i) {
        if (flowers[i] == 0 and not std::empty(DQ)) {
          acc += std::size(DQ) / k;
          DQ.clear();
        }
        else if (flowers[i] == 0 and std::empty(DQ)) {
          continue;
        }
        else if (flowers[i] == 1) {
          DQ.emplace_back(flowers[i]);
          if (i == n - 1)
            acc += std::size(DQ) / k;
        } 
      }
      return acc >= m;
    };


    auto bsearch = [&]() {
      std::optional<int> result = {};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (check(mid) == true) {
          result.emplace(mid);
          go(lo, mid - 1);
        }
        else {
          go(mid + 1, hi);
        }
      };
      return go(1, *std::max_element(std::begin(bloomDay), std::end(bloomDay))), result;
    };


    const auto solution = bsearch().value_or(-1);

    return solution;
  }
};
