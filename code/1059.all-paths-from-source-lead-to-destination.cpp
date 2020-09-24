class Solution {
 public:
  bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
    enum color_t {untouched, explore, done};
    
    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);      
      for (const auto &e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
      }
      return self;
    }();

    const struct {
      mutable color_t status[10000] = {};
      mutable bool valid = true;
    } ST;

    std::function<void(int)> fold_cycle = [&](int u) {
      if (ST.status[u] == explore) {
        ST.valid = false;
        return;
      }
      else {
        if (std::empty(G[u]) and u != destination) {
          ST.valid = false;
          return;
        }
        else {
          ST.status[u] = explore;
          for (const auto v : G[u]) {
            if (ST.status[v] != done) {
              fold_cycle(v);
            }
            if (not ST.valid) {
              return;
            }
          }
          ST.status[u] = done;
        }
      }
    };

    return fold_cycle(source), ST.valid;
  }
};

