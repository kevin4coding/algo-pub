class Solution {
 public:
  int getLastMoment(int n, vector<int>& left, vector<int>& right) {
    const auto solution = [&](int acc = INT_MIN) {
      for (const auto x : left) {
        acc = std::max(acc, x);
      }
      for (const auto x : right) {
        acc = std::max(acc, n - x);
      }
      return acc;
    }();

    return solution;
  }
};
