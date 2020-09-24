class Solution {
 public:
  int mctFromLeafValues(vector<int>& arr) {
    const int n = std::size(arr);

    const auto PGE = [&, DQ = std::deque<int>{}](std::vector<std::optional<int>> self = {}) mutable {
      self.resize(n, std::optional<int>{});
      for (int i = 0; i < n; ++i) {
        while (not std::empty(DQ) and DQ.front() < arr[i]) {
          DQ.pop_front();
        }
        if (not std::empty(DQ)) {
          self[i].emplace(DQ.front());
        }
        DQ.emplace_front(arr[i]);
      }
      return self;
    }();

    const auto NGE = [&, DQ = std::deque<int>{}](std::vector<std::optional<int>> self = {}) mutable {
      self.resize(n, std::optional<int>{});
      for (int i = n - 1; i >= 0; --i) {
        while (not std::empty(DQ) and DQ.front() <= arr[i]) {
          DQ.pop_front();
        }
        if (not std::empty(DQ)) {
          self[i].emplace(DQ.front());
        }
        DQ.emplace_front(arr[i]);
      }
      return self;
    }();
    
    const auto solution = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        // max element should be on top.
        if (not NGE[i] and not PGE[i]) {
          continue;
        }
        else {
          acc += arr[i] * std::min(NGE[i].value_or(INT_MAX), PGE[i].value_or(INT_MAX));
        }
      }
      return acc;
    }();
    
    return solution;
  }
};
