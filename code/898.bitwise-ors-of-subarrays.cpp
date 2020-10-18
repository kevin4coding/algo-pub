class Solution {
 public:
  int subarrayBitwiseORs(vector<int>& A) {
    const int n = std::size(A);

    const auto solution = [&n, A = A](std::unordered_set<int> self = {}) mutable {
      for (int i = 0; i < n; ++i) {
        self.insert(A[i]);
        for (int j = i - 1; j >= 0; --j) {
          if ((A[j] | A[i]) == A[j]) {
            break;
          }
          else {
            self.insert(A[j] |= A[i]);
          }
        }
      }
       return self;
    }();

    return std::size(solution);
  }
};
 
