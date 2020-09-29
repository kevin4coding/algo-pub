struct trie_node_t {
  bool is_word;
  std::unordered_map<char, trie_node_t*> next;
  trie_node_t() = default;
  explicit trie_node_t(bool is_word) : is_word(is_word) {}
};


struct trie_t {
  trie_node_t* root;

  trie_t() : root{new trie_node_t()} {}

  explicit trie_t(const std::vector<std::string> words) : root{new trie_node_t()} {
    for (const auto & x: words) {
      if (not std::empty(x)) {
        insert(x);
      }
    }
  }

  void insert(const std::string& s) {
    std::function<void(trie_node_t*, int)> fold = [&](trie_node_t* n, int i) {
      if (i == std::size(s)) {
        n->is_word = true;
      }
      else {
        n->next.try_emplace(s[i], new trie_node_t(false));
        fold(n->next[s[i]], i + 1);
      }
    };
    return fold(root, 0);
  }
  
  bool check(const std::string& s) const {
    std::function<bool(trie_node_t*, int)> fold = [&](trie_node_t* n, int i) {
      if (i == std::size(s)) {
        return n->is_word;
      }
      else if (not n->next.count(s[i])) {
        return false;
      }
      else {
        return fold(n->next[s[i]], i + 1);
      }
    };
    return fold(root, 0);
  }

  bool is_concat(const string& str) const {
    std::function<bool(trie_node_t*, int, int)> fold = [&](trie_node_t* n, int i, int cnt) {
      const char ch = str[i];
      if (i == std::size(str)) {
        return n->is_word and cnt >= 1;
      }
      else if (not n->next.count(ch)) {
        return false;
      }
      else if (n->next[ch]->is_word) {
        return fold(root, i + 1, cnt + 1) or fold(n->next[ch], i + 1, cnt);
      }
      else {
        return fold(n->next[ch], i + 1, cnt);
      }
    };

    return fold(root, 0, 0);
  }
};
  

class Solution {
 public:
  vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
    const auto trie = trie_t(words);

    const auto solution = [&](std::vector<std::string> self = {}) {
      std::copy_if(std::begin(words), std::end(words), std::back_inserter(self), [&](const auto & x) {
        return trie.is_concat(x);
      });
      return self;
    }();
    
    return solution;
  }
};
