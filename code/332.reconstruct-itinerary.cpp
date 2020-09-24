class Solution {
public:
  vector<string> findItinerary(vector<vector<string>> tickets) {
    auto make_graph = [&](std::unordered_map<std::string, std::multiset<std::string>> self = {}) {
      for (const auto& t : tickets) {
        self[t[0]].emplace(t[1]);
      }
      return self;
    };

    const auto solution = [&](std::vector<std::string> self = {}) {
      std::function<void(const std::string&)> fold = [&, G = make_graph()](const std::string& u) mutable {
        while (not std::empty(G[u])) {
          auto v = *std::begin(G[u]);
          G[u].erase(std::begin(G[u]));
          fold(v);
        }
        self.emplace_back(u);
      };

      return fold("JFK"), std::reverse(std::begin(self), std::end(self)), self;
    }();

    return solution;
  }
};
