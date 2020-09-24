class Solution {
 public:
  int maxScore(vector<int>& cardPoints, int k) {
    const int n = std::size(cardPoints);
    
    const auto min_windowsum = [&, DQ = std::deque<int>{}, subacc_sum = int(0)](int acc = INT_MAX) mutable {
      for (int i = 0; i < n; ++i) {
        subacc_sum += DQ.emplace_back(cardPoints[i]);
        while (std::size(DQ) > n - k) {
          subacc_sum -= DQ.front();
          DQ.pop_front();
        }
        if (std::size(DQ) == n - k) {
          acc = std::min(acc, subacc_sum);
        }
      }
      return acc;
    }();
    
    const auto solution = std::accumulate(std::begin(cardPoints), std::end(cardPoints), 0) - min_windowsum;

    return solution;
        
  }
};
