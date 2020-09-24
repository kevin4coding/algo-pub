class Solution {
 public:
  int openLock(vector<string>& deadends, string target) {
    struct {
      mutable std::deque<std::string> Q = {};
      mutable std::unordered_map<std::string, std::optional<int>> D = {}; 
    } ST;

    const auto deadend_set = std::unordered_set<std::string>(std::begin(deadends), std::end(deadends));

    auto init_ST = [&]() {
      if (not deadend_set.count("0000")) {
        ST.Q.emplace_back("0000");
        ST.D["0000"] = 0;
      }
    };

    auto rotate_rr = [](std::string key, int pos) {
      std::exchange(key[pos], static_cast<char>('0' + (key[pos] - '0' + 1) % 10));
      return key;
    };

    auto rotate_ll = [](std::string key, int pos) {
      std::exchange(key[pos], static_cast<char>('0' + (key[pos] - '0' - 1 + 10) % 10));
      return key;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q) or D[target].has_value()) {
        return;
      }
      else {
        const auto curr_w = Q.front();
        Q.pop_front();
        for (int i = 0; i < 4; ++i) {
          const auto next_w_rr = rotate_rr(curr_w, i);
          const auto next_w_ll = rotate_ll(curr_w, i);
          if (not D[next_w_rr].has_value() and not deadend_set.count(next_w_rr)) {
            D[next_w_rr] = D[curr_w].value() + 1;
            Q.emplace_back(next_w_rr);
          }
          if (not D[next_w_ll].has_value() and not deadend_set.count(next_w_ll)) {
            D[next_w_ll] = D[curr_w].value() + 1;
            Q.emplace_back(next_w_ll);                                           
          }
        }
        return bfs();
      }
    };
    
    return (init_ST(), bfs(), ST.D[target].value_or(-1));
  }
};

