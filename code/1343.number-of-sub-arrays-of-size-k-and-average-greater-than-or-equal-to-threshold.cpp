class Solution {
 public:
  int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    const int n = std::size(arr);    
    
    const auto solution = [&, DQ = std::deque<int>{}, subacc_sum = int{0}](int acc = 0) mutable {
      for (int i = 0; i < n; ++i) {
        DQ.emplace_back(arr[i]);
        subacc_sum += arr[i];
        while (std::size(DQ) > k) {
          subacc_sum -= DQ.front();
          DQ.pop_front();
        }
        if (std::size(DQ) == k and subacc_sum >= threshold * k) {
          ++acc;
        }
      }
      return acc;
    }();

    return solution;
  }
};
