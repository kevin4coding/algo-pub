class Solution {
 public:
  vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
    struct {
      mutable std::deque<int> Q = {};
      mutable bool vis[105] = {};
      mutable int level = 0;
    } ST;

    auto init_ST = [&]() {
      ST.Q.emplace_back(id);
      ST.vis[id] = true;
    };


    std::function<void(void)> bfs = [&, &Q = ST.Q, &vis = ST.vis]() {
      if (ST.level == level or std::empty(Q)) {
        return;
      }
      else {
        const auto curr_level = std::vector<int>(std::begin(Q), std::end(Q));
        Q.clear();
        ++ST.level;
        for (const auto u : curr_level) {
          for (const auto v : friends[u]) {
            if (not vis[v]) {
              vis[v] = true;
              Q.emplace_back(v);
            }
          }
        }
        return bfs();
      }
    };

    auto sorter = [&](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) {
      if (p1.second == p2.second) {
        return p1.first < p2.first;
      }
      else {
        return p1.second < p2.second;
      }
    };

    const auto solution = [&](std::vector<std::string> self = {}) {
      init_ST();
      bfs();
      
      const auto freq_map = [&](std::unordered_map<std::string, int> x = {}) {
        for (const auto i : ST.Q) {
          for (const auto movie : watchedVideos[i]) {
            x[movie]++;
          }
        }
        return x;
      }();
      
      const auto bucket_vec = [&](std::vector<std::pair<std::string, int>> x = {}) {
        std::copy(std::begin(freq_map), std::end(freq_map), std::back_inserter(x));
        std::sort(std::begin(x), std::end(x), sorter);
        return x;
      }();

      std::transform(std::begin(bucket_vec), std::end(bucket_vec), std::back_inserter(self), [&](auto &&x) {
        return x.first;
      });
      return self;
      
    }();

    return solution;
    
  }
};
