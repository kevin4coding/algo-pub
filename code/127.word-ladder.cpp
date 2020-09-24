class Solution {
 public:
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    const struct {
      mutable std::deque<std::string> Q;
      mutable std::unordered_map<std::string, std::optional<int>> D;
    } ST;

    const auto word_set = std::unordered_set<std::string>(std::begin(wordList), std::end(wordList));

    auto init_ST = [&]() {
      ST.Q.emplace_back(beginWord);
      ST.D[beginWord] = 1;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q) or D[endWord].has_value()) {
        return;
      }
      else {
        const auto curr_w = Q.front();
        Q.pop_front();
        for (int i = 0; i < std::size(curr_w); ++i) {
          for (char ch = 'a'; ch <= 'z'; ++ch) {
            const auto next_w = [&](std::string self = {}) {
              std::exchange(self, curr_w);
              std::exchange(self[i], ch);
              return self;
            }();
            if (word_set.count(next_w) and not D[next_w].has_value()) {
              D[next_w] = D[curr_w].value() + 1;
              Q.emplace_back(next_w);
            }
          }
        }
        bfs();
      }
    };

    return (init_ST(), bfs(), ST.D[endWord].value_or(0));
  }
};
