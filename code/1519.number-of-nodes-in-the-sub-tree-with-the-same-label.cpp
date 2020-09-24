#pragma GCC optimize ("O3")
#pragma GCC target ("sse4.1")
static const int _ = []() { return (ios::sync_with_stdio(false), cin.tie(nullptr), 0); }();

#pragma comment(linker,"/STACK:1024000000,1024000000") 

std::optional<int> f_memo[100000][26];


class Solution {
 private:
  int f(int i, int j, const std::vector<std::vector<int>>& G, const std::string& labels) {
    
    if (f_memo[i][j].has_value()) {
      return f_memo[i][j].value();
    }
    else {
      return f_memo[i][j].emplace([&] {
        if (std::empty(G[i])) {
          return static_cast<int>(labels[i] - 'a' == j);
        }
        else {
          return [&]() {
            auto acc = static_cast<int>(labels[i] - 'a' == j);
            for (const auto k : G[i]) {
              acc += f(k, j, G, labels);
            }
            return acc;
          }();
        }
      }());
    }
  };
  
  void fold(int u, std::optional<int> prev,
            std::vector<std::vector<int>>& G,
            const std::vector<std::vector<int>>& G_undirected,
            std::vector<bool>& vis) {
    if (prev.has_value()) {
      G[prev.value()].emplace_back(u);
    }
    vis[u] = true;
    for (const auto v : G_undirected[u]) {
      if (not vis[v]) {
        fold(v, u, G, G_undirected, vis);
      }
    }
  };
 public:
  vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
    // static const struct {
    //   mutable std::optional<int> f[100000][26];

    //   void reset(int n) const {
    //     for (int i = 0; i < n; ++i) {
    //       for (int j = 0; j < 26; ++j) {
    //         f[i][j].reset();
    //       }
    //     }
    //   }
    // } mempool;

    // mempool.reset(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 26; ++j) {
        f_memo[i][j].reset();
      }
    }

    const auto G_undirected = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(n);
      for (const auto e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        self[u].emplace_back(v);
        self[v].emplace_back(u);
      }
      return self;
    }();


    

    const auto G = [&](std::vector<std::vector<int>> self = {}) {
      auto vis = std::vector<bool>(n, false);
      self.resize(n);
      fold(0, nullopt, self, G_undirected, vis);
      return self;
      // std::function<void(int, std::optional<int>)> fold = [&](int u, std::optional<int> prev) {
      //   if (prev.has_value()) {
      //     self[prev.value()].emplace_back(u);
      //   }
      //   vis[u] = true;
      //   for (const auto v : G_undirected[u]) {
      //     if (not vis[v]) {
      //       fold(v, u);
      //     }
      //   }
      // };

      // return fold(0, std::nullopt), self;
    }();
      
    // std::function<int(int, int)> f = [&, memo = std::ref(mempool.f)](int i, int j) {
    //   if (memo[i][j].has_value()) {
    //     return memo[i][j].value();
    //   }
    //   else {
    //     return memo[i][j].emplace([&] {
    //       if (std::empty(G[i])) {
    //         return static_cast<int>(labels[i] - 'a' == j);
    //       }
    //       else {
    //         return [&]() {
    //           auto acc = static_cast<int>(labels[i] - 'a' == j);
    //           for (const auto k : G[i]) {
    //             acc += f(k, j);
    //           }
    //           return acc;
    //         }();
    //       }
    //     }());
    //   }
    // };

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(n);
      for (int i = 0; i < n; ++i) {
        self[i] = f(i, labels[i] - 'a', G, labels);
      }
      return self;
    }();



    return solution;
  }
};
