class Solution {
 public:
  bool canReach(vector<int>& arr, int start) {
    struct {
      mutable std::deque<int> Q = {};
      mutable std::optional<int> D[50000] = {};
      mutable bool reached = false;
    } ST;


    auto init_ST = [&]() {
      ST.Q.emplace_back(start);
      ST.D[start] = 0;
      if (arr[start] == 0) {
        ST.reached = true;
      }
    };


    auto inbound = [&](int i) {
      return 0 <= i and i < std::size(arr);
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q) or ST.reached == true) {
        return;
      }
      else {
        const auto u = Q.front();
        Q.pop_front();
        for (const auto v : std::array{u + arr[u], u - arr[u]}) {
          if (inbound(v) and not D[v].has_value()) {
            D[v] = D[u].value() + 1;
            Q.emplace_back(v);
            if (arr[v] == 0) {
              ST.reached = true;
            }
          }
        }
        return bfs();
      }
    };

    return init_ST(), bfs(), ST.reached;
    
  }
};
