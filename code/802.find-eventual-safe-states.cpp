class Solution {
 public:
  vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    enum color {untouched, explore, done};

    struct {
      mutable std::vector<int> color;
    } ST;
    
    std::function<bool(int)> fold_cycle = [&](int u) {
      if (ST.color[u] == explore) {
        return true;
      }
      else if (ST.color[u] == done) {
        return false;
      }
      else {
        ST.color[u] = explore;
        for (const auto v : graph[u]) {
          if (ST.color[v] != done and fold_cycle(v)) {
            return true;
          }
        }
        ST.color[u] = done;
        return false;
      }
    };

    const auto solution = [&](std::vector<int> self = {}) {
      ST.color.resize(std::size(graph), untouched);
      
      for (int i = 0; i < std::size(graph); ++i) {
        if (not fold_cycle(i)) {
          self.emplace_back(i);
        }
      }
      return self;
    }();

    return solution;
  }
};
