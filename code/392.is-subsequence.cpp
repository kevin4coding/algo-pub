class Solution {
 public:
  bool isSubsequence(string s, string t) {
    const int n = std::size(s);
    const int m = std::size(t);
    
    std::function<bool(int, int)> fold = [&](int i, int j) {
      if (i == n) {
        return true;
      }
      else if (j == m) {
        return false;
      }
      else if (s[i] == t[j]) {
        return fold(i + 1, j + 1);
      }
      else {
        return fold(i, j + 1);
      }
    };

    return fold(0, 0);
  }
};
