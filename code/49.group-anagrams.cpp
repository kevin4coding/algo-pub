class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    auto sorted = [&](std::string s) {
      std::sort(std::begin(s), std::end(s));
      return s;
    };
    
    const auto groups_map = [&](std::unordered_map<std::string, std::vector<std::string>> self = {}) {
      for (const auto & s : strs) {
        self[sorted(s)].emplace_back(s);
      }
      return self;
    }();

    const auto solution = [&](std::vector<std::vector<std::string>> self = {}) {
      for (const auto & [_, group] : groups_map) {
        self.emplace_back(group);
      }
      return self;
    }();

    return solution;
  }
};
