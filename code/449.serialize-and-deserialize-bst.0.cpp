class basic_tokenizer {
 private:
  mutable std::stringstream stream;
 public:
  basic_tokenizer(const string& str) :  stream(str){};
 public:
  bool has_next() { return stream.peek() != std::char_traits<char>::eof();}
  char peek() { return stream.peek(); }
  void consume() { next<char>(); };

 public:
  template <class T, typename std::enable_if_t<std::is_arithmetic_v<T>
                                               or std::is_same_v<string, T>>* = nullptr>
  T next() {
    auto data = T{};
    stream >> data;
    return data;
  }
};

class Codec {
 public:
  string serialize(TreeNode* root) {
    auto stream = std::stringstream{};
    std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        return;
      }
      else {
        stream << (n == root ? "" : " ") << n->val;
        fold(n->left);
        fold(n->right);
      }
    };
    return fold(root), stream.str();
  }
 
  TreeNode* deserialize(string data) {        
    auto DQ = [&](std::deque<int> self = {}) {
      auto token = basic_tokenizer(data);
      while (token.has_next()) {
        self.emplace_back(token.next<int>());
      }
      return self;
    }();
        
    std::function<TreeNode*(int, int)> build = [&](int lo, int hi) {
      if (std::empty(DQ) or (DQ.front() < lo or DQ.front() > hi)) {
        return static_cast<TreeNode*>(nullptr);
      }
      else {
        const auto val = DQ.front();
        DQ.pop_front();
        return new TreeNode(val, build(lo, val), build(val, hi));
      }
    };
    
    return fold(INT_MIN, INT_MAX);
  }
};
