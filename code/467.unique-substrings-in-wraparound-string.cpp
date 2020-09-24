class Solution {
 public:
  int findSubstringInWraproundString(string p) {
    const int n = std::size(p);

    // calculate the longest increasing subarray ending with 'a,...,z' for p. 
    const auto LICS = [&, DQ = std::deque<char>{}](std::vector<int> acc = {}) mutable {
      acc.resize(26, 0);
      for (int i = 0; i < n; ++i) {
        if (not std::empty(DQ) and (DQ.back() + 1 == p[i] or (DQ.back() == 'z' and p[i] == 'a'))) {
          DQ.emplace_back(p[i]);
        }
        else {
          DQ.clear();
          DQ.emplace_back(p[i]);
        }
        acc[DQ.back() - 'a'] = std::max(acc[DQ.back() - 'a'], (int) std::size(DQ));
      }
      return acc;
    }();

    return std::accumulate(std::begin(LICS), std::end(LICS), 0);
  }
};


