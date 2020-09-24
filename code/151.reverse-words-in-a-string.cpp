class Solution {
 public:
  string reverseWords(string s) {
    const int n = std::size(s);

    auto next = [&](int i) {
      auto acc = std::string{};
      for (; i < n; ++i) {
        if (s[i] == ' ') {
          break;
        }
        else {
          acc.push_back(s[i]);
        }
      }
      return std::pair{acc, i};
    };

    const auto words = [&](std::vector<std::string>  self = {}) {
      std::function<void(int)> fold = [&](int i) {
        if (i == n) {
        }
        else if (s[i] == ' ') {
          return fold(i + 1);
        }
        else {
          const auto [word, next_i] = next(i);
          self.emplace_back(word);
          return fold(next_i);
        }
      };

      return fold(0), self;
    }();

    const auto solution = [&](std::string self = {}) {
      for (int i = std::size(words) - 1; i >= 0; --i) {
        self += words[i] + (i > 0 ? " " : "");
      }
      return self;
    }();

    return solution;
  }
};

