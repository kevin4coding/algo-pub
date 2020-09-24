class Solution {
 public:
  string stringShift(string s, vector<vector<int>>& shift) {
    const auto solution = [&, DQ = std::deque<char>(std::begin(s), std::end(s))](std::string self = {}) mutable {
      for (const auto & s : shift) {
        const auto [dir, amt] = std::pair{s[0], s[1]};
        if (dir == 0) {
          for (int k = 0; k < amt; ++k) {
            DQ.emplace_back(DQ.front());
            DQ.pop_front();
          }
        }
        else if (dir == 1) {
          for (int k = 0; k < amt; ++k) {
            DQ.emplace_front(DQ.back());
            DQ.pop_back();
          }
        }
      }
      std::copy(std::begin(DQ), std::end(DQ), std::back_inserter(self));
      return self;
    }();

    return solution;
  }
};
