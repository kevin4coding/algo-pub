class Solution {
 public:
  int findCircleNum(vector<vector<int>>& M) {
    const int N = std::size(M);
    
    struct state_t {
      mutable std::vector<bool> visited;
    };

    const auto ST = [&](state_t self = {}) {
      self.visited.resize(N, false);
      return self;
    }();

    std::function<void(int)> fold = [&](int v) {
      ST.visited[v]= true;
      for (int u = 0; u < N; ++u) {
        if (not ST.visited[u] and M[v][u] == 1 and u != v) {
          fold(u);
        }
      }
    };
       
    const auto solution = [&](int acc = 0) {
      for (int v = 0; v < N; ++v) {
        if (not ST.visited[v]) {
          ++acc;
          fold(v);
        }
      }
      return acc;
    }();

    return solution;
  }
};
