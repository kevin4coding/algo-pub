class Solution {
 public:
  string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
    const auto parent = [&](std::unordered_map<std::string, std::string> self = {}) {
      for (const auto & region : regions) {
        if (std::size(region) > 0) {
          const auto father = region[0];
          for (int i = 1; i < std::size(region); ++i) {
            self[region[i]] = father;
          }
        }
      }
      return self;
    }();


    const auto chain1 = [&](std::unordered_set<std::string> self = {}) {
      std::function<void(std::string)> take = [&](const std::string& x) {
        self.emplace(x);
        if (parent.count(x)) {
          take(parent.at(x));
        }
      };
      return take(region1), self;
    }();

    std::function<std::string(std::string)> solve = [&](std::string x) {
      return chain1.count(x) ? x : solve(parent.at(x));
    };


    return solve(region2);
  }
};
