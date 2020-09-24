class Solution {
 public:
  int numTimesAllBlue(vector<int>& light) {
    const int n = std::size(light);
    
    const auto solution = [&, right_most = int{0}](int acc = 0) mutable {
      for (int i = 0; i < n; ++i) {
        right_most = std::max(right_most, light[i]);
        if (right_most == i + 1)
          ++acc;
      }
      return acc;
    }();

    return solution;
  }
};
