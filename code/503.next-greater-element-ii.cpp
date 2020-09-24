class Solution {
 public:
  vector<int> nextGreaterElements(vector<int>& nums) {
    const int N = std::size(nums);
    
    const auto arr = [&](std::vector<int> self = {}) {
      std::copy(std::begin(nums), std::end(nums), std::back_inserter(self));
      std::copy(std::begin(nums), std::end(nums), std::back_inserter(self));
      return self;
    }();
    
    const auto solution = [&, DQ = std::deque<int>{}](std::vector<int> self = {}) mutable {
      self.resize(N, -1);
      for (int i = 2 * N - 1; i >= 0; --i) {
        while (not std::empty(DQ) and arr[DQ.front()] <= arr[i]) {
          DQ.pop_front();
        }
        if (not std::empty(DQ)) {
          self[i % N] = arr[DQ.front()];
        }
        DQ.emplace_front(i);
      }
      return self;
    }();

    return solution;
  }
};
