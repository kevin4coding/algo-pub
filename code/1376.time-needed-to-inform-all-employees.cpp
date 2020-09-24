class Solution {
 public:
  int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (int u = 0; u < n; ++u) {
        if (manager[u] != -1) {
          self[manager[u]].emplace_back(u);
        }
      }
      return self;
    }();

    std::function<int(int)> fold = [&](int u) {
      if (std::empty(G[u])) {
        return 0;
      }
      else {
        return [&]()  {
          auto acc = informTime[u];
          for (const auto v : G[u]) {
            acc = std::max(acc, informTime[u] + fold(v));
          }
          return acc;
        }();
      }
    };

    return fold(headID);
    
  }
};

