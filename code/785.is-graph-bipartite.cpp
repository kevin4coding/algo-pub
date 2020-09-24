class Solution {
 public:
  bool isBipartite(vector<vector<int>>& graph) {
    const int black = 0;
    const int white = 1;
    
    struct {
      mutable std::deque<std::pair<int, int>> Q;
      mutable std::optional<int> color[100];
      mutable std::optional<int> is_bipartite;
    } ST;

    const int n = std::size(graph);

    std::function<void(void)> bfs = [&]() {
      if (std::empty(ST.Q) or ST.is_bipartite.has_value()) {
        return;
      }
      else {
        const auto [u, color] = ST.Q.front();
        ST.Q.pop_front();
        for (const auto v : graph[u]) {
          if (not ST.color[v].has_value()) {
            ST.color[v] = ~color;
            ST.Q.emplace_back(v, ~color);
          }
          else if (ST.color[v] == color) {
            ST.is_bipartite = false;
          }
          else if (ST.color[v] == ~color) {
            // do nothing 
          }
        }
        bfs();
      }
    };

    const auto solution = [&]() {
      for (int u = 0; u < n; ++u) {
        if (not ST.color[u].has_value()) {
          std::exchange(ST.Q, std::deque{std::pair{u, black}});
          std::exchange(ST.color[u], black);
          bfs();
        }
      }
      return ST.is_bipartite.value_or(true);
    }();

    return solution;
        
  }
};
