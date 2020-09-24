class Solution {
 public:
  int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
    const int n = std::size(startTime);
    
    const auto solution = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        if (startTime[i] <= queryTime and queryTime <= endTime[i]) {
          ++acc;
        }
      }
      return acc;
    }();

    return solution;
  }
};
