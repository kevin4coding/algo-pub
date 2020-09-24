class basic_tokenizer {
 private:
  mutable std::stringstream stream;
 public:
  basic_tokenizer(const string& str) : stream(str){};
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

class Solution {
 public:
  TreeNode* str2tree(string s) {
    auto token = basic_tokenizer(s);
    
    std::function<TreeNode*(void)> build = [&]()  {
      if (not token.has_next()) {
        return static_cast<TreeNode*>(nullptr);
      }
      else {
        auto res = new TreeNode(token.next<int>());
        if (token.has_next() and token.peek() == '(') {
          token.consume();
          res->left = build();
          token.consume();
        }
        if (token.has_next() and token.peek() == '(') {
          token.consume();
          res->right = build();
          token.consume();
        }
        return res;
      }
    };

    return build();   
  }
};
