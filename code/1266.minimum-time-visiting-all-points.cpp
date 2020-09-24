class Solution {
 public:
  int minTimeToVisitAllPoints(vector<vector<int>>& points) {
    const int n = std::size(points);

    auto distance = [&](const std::vector<int>& p1, const std::vector<int>& p2) {
      return std::max(std::abs(p1[0] - p2[0]), std::abs(p1[1] - p2[1]));
    };
    
    const auto solution = [&](int acc = 0) {
      for (int i = 1; i < n; ++i) {
        acc += distance(points[i - 1], points[i]);
      }
      return acc;
    }();

    return solution;
    
  }
};
