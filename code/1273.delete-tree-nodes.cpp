class Solution {
 public:
  int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
    const struct {
      mutable std::optional<int> f[10000];
      mutable std::optional<int> g[10000];
    } mempool;
    
    const int root = *std::find(std::begin(parent), std::end(parent), -1);
    const int n = nodes;

    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
          self[parent[i]].emplace_back(i);
        }
      }
      return self;
    }();

    std::function<int(int)> f = [&, memo = std::ref(mempool.f)](int u) {
      if (memo[u].has_value()) {
        return memo[u].value();
      }
      else {
        return memo[u].emplace([&] {
          if (std::empty(G[u])) {
            return value[u];
          }
          else {
            return [&]() {
              auto acc = value[u];
              for (const auto v : G[u]) {
                acc += f(v);
              }
              return acc;
            }();
          }
        }());
      }
    };

    std::function<int(int)> g = [&, memo = std::ref(mempool.g)](int u) {
      if (memo[u].has_value()) {
        return memo[u].value();
      }
      else {
        return memo[u].emplace([&] {
          if (std::empty(G[u])) {
            return 1;
          }
          else {
            return [&](int acc = 1) {
              for (const auto v : G[u]) {
                acc += g(v);
              }
              return acc;
            }();
          }
        }());
      }
    };


    const auto zero_subtrees = [&](std::vector<std::pair<int, int>> self = {}) {
      std::function<void(int)> fold = [&](int u) {
        if (f(u) == 0) {
          self.emplace_back(std::pair{u, g(u)});
          return;
        }
        else if (std::empty(G[u])) {
          return;
        }
        for (const auto v : G[u]) {
          fold(v);
        }
      };
      return fold(0), self;
    }();

    const auto zero_subtree_size = [&](int acc = 0) {
      for (const auto [v, n] : zero_subtrees) {
        acc += n;
      }
      return acc;
    }();

    const auto solution = g(0) - zero_subtree_size;


    return solution;
    
  }
};
