class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    const int n = std::size(s);
    
    const auto solution = [&, DQ = std::deque<int>{}, SET = std::unordered_set<char>{}](int acc = 0) mutable {
      for (int i = 0; i < n; ++i) {
        DQ.emplace_back(s[i]);
        while (SET.count(s[i])) {
          SET.erase(DQ.front());
          DQ.pop_front();
        }
        SET.emplace(s[i]);
        acc = std::max(acc, static_cast<int>(std::size(DQ)));
      }
      return acc;
    }();

    return solution;
    
  }
};
