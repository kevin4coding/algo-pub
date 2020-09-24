class Solution {
 public:
  bool canVisitAllRooms(vector<vector<int>>& rooms) {
    const int N = std::size(rooms);
    
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(N, std::vector<int>{});
      for (int u = 0; u < N; ++u) {
        for (const auto v : rooms[u]) {
          self[u].emplace_back(v);
        }
      }
      return self;
    }();

    const auto CC_cnt = [&](int acc = 0) {
      //mutable 
      auto visited = std::vector<bool>(N, false);
      std::function<void(int)> fold = [&](int u) {
        visited[u] = true;
        for (const auto v : G[u]) {
          if (not visited[v]) {
            fold(v);
          }
        }
      };

      for (int u = 0; u < N; ++u) {
        if (not visited[u]) {
          ++acc;
          fold(u);
        }
      }
      return acc;
    }();
    
    return CC_cnt == 1;
  }
};
