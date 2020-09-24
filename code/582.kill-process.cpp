class Solution {
 public:
  vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
    const int n = std::size(pid);
    
    const auto children_map = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      for (int i = 0; i < n; ++i) {
        self[ppid[i]].emplace_back(pid[i]);
      }
      return self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      std::function<void(int)> fold = [&](int i) {
        self.emplace_back(i);
        if (children_map.count(i)) {
          for (const auto ch : children_map.at(i)) {
            fold(ch);
          }
        }
      };
      return fold(kill), self;
    }();

    return solution;
  }
};
