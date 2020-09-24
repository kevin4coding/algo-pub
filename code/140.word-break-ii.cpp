struct trie_t {
  bool is_word;
  std::shared_ptr<trie_t> next[256];
  
  trie_t() = default;

  explicit trie_t(bool d) : is_word{d} {}

  explicit trie_t(const std::vector<std::string>& dict) : is_word{false}, next{} {
    for (const auto & word : dict) {
      insert(word);
    }
  }

  std::shared_ptr<trie_t> insert(const std::string& s, int i = 0) {
    const int n = std::size(s);
    if (next[s[i]] == nullptr) {
      next[s[i]] = std::make_shared<trie_t>(i == (n - 1));
    }
    else {
      next[s[i]]->is_word |= (i == (n - 1));
    }
    return i == n - 1 ? next[s[i]] : next[s[i]]->insert(s, i + 1);
  };

  bool find_word(const std::string& s, int i = 0) {
    const int n = std::size(s);
    if (next[s[i]] == nullptr) {
      return false;
    }
    else {
      return (i == n - 1) ? next[s[i]]->is_word : next[s[i]]->find_word(s, i + 1);
    }
  }
};

class Solution {
 public:
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    s = "$" + s; // padding
    
    static struct {
      mutable std::optional<bool> f[2000] = {};

      void reset(int r) {
        for (int i = 0; i <= r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    const int n = std::size(s);
    mempool.reset(n);

    const auto trie = std::make_shared<trie_t>(wordDict);

    std::function<bool(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return true;
          }
          else {
            return [&](bool acc = false) {
              for (int k = 1; k <= i; ++k) {
                acc |= trie->find_word(s.substr(k, i - k + 1)) and f(k - 1);
              }
              return acc;
            }();
          }
        }());
      }
    };

    const auto solution = [&](std::vector<std::string> self = {}) {
      struct {
        mutable std::vector<std::vector<std::string>> acc = {};
        mutable std::vector<std::string> cache = {};
      } ST;

      std::function<void(int)> fold = [&](int i) {
        if (i == 0) {
          std::reverse(std::begin(ST.cache), std::end(ST.cache));
          ST.acc.emplace_back(ST.cache);
          std::reverse(std::begin(ST.cache), std::end(ST.cache));
          return;
        }
        else {
          for (int k = 1; k <= i; ++k) {
            const auto word_rr = s.substr(k, i - k + 1);
            if (trie->find_word(word_rr) and f(k - 1)) {
              ST.cache.emplace_back(word_rr);
              fold(k - 1);
              ST.cache.pop_back();
            }
          }
        }
      };

      auto join = [&](const std::vector<std::string>& arr) {
        const int n = std::size(arr);
        auto x = std::string{};
        for (int i = 0; i < n; ++i) {
          x += arr[i] + (i < n - 1 ? " " : "");
        }
        return x;
      };

      return (fold(n - 1),
              std::transform(std::begin(ST.acc), std::end(ST.acc), std::back_inserter(self), join),
              self);
    }();

    return solution;
  }
};
