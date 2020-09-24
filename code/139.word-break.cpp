// memory safe trie
struct trie_t {
  bool is_word;
  std::shared_ptr<trie_t> next[256];

  trie_t() = default;

  explicit trie_t(bool d) : is_word{d} {}
  
  explicit trie_t(const std::vector<std::string>& dict) : is_word{false}, next{} {
    for (const auto& word : dict) {
      insert(word);
    }
  }

  std::shared_ptr<trie_t> insert(const std::string& s, int i = 0) {
    if (next[s[i]] == nullptr) {
      next[s[i]] = std::make_shared<trie_t>(i == (std::size(s) - 1));
    }
    else {
      next[s[i]]->is_word |= (i == std::size(s) - 1);
    }
    return i == std::size(s) - 1 ? next[s[i]] : next[s[i]]->insert(s, i + 1);
  }

  bool check_word(const std::string & s, int i = 0) {
    if (next[s[i]] == nullptr) {
      return false;
    }
    return i == std::size(s) - 1 ? next[s[i]]->is_word : next[s[i]]->check_word(s, i + 1);
  }
};

class Solution {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    static struct {
      mutable std::optional<bool> f[2000];

      void reset(int r) {
        for (int i = 0; i <= r; ++i) {
          f[i].reset();
        }
      }
    } mempool;

    s = "#" + s;
    const int n = std::size(s);

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
                acc |= trie->check_word(s.substr(k, i - k + 1)) and f(k - 1);
              }
              return acc;
            }();
          }
        }());
      }
    };

    return mempool.reset(n), f(n - 1);
  }
};
