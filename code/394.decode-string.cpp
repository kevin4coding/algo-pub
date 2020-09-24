/* BNF Grammar :
 * MetaExpr -> Expr*
 * Expr -> Word | RWord
 * Word -> String
 * RWord -> Num[MetaExpr]
 */

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


class Solution {
 public:
  string decodeString(string s) {
    auto token = basic_tokenizer(s);
    std::function<std::string(void)> MetaExpr, Expr, Word, RWord;

    auto next_valid_string = [&](std::string acc = {}) {
      while (token.has_next() and std::isalpha(token.peek())) {
        acc.push_back(token.next<char>());
      }
      return acc;
    };

    MetaExpr = [&]() {
      auto acc = std::string{};
      while (token.has_next() and token.peek() != ']') {
        acc += Expr();
      }
      return acc;
    };

    Expr = [&]() {
      if (std::isalpha(token.peek())) {
        return next_valid_string();
      }
      else {
        return RWord();
      } 
    };

    RWord = [&]() {
      auto acc = std::string{};
      const auto num = token.next<int>();
      token.consume();
      const auto meta_expr = MetaExpr();
      token.consume();
      for (int i = 0; i < num; ++i) {
        acc += meta_expr;
      }
      return acc;
    };

    return MetaExpr();    
  }
};
