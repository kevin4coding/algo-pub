`/* BNF Grammar
   Expr = Int | Bool | (Bool ? Expr : Expr);
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
  string parseTernary(string expression) {
    auto token = basic_tokenizer(expression);
    std::function<std::string(void)> Expr = [&]() {
      if (std::isdigit(token.peek())) {
        return std::to_string(token.next<int>());
      }
      else {
        const char bool_val = token.next<char>();
        if ((token.has_next() and token.peek() == ':') or token.has_next() == false) {
          return std::string(1, bool_val);
        }
        else {
          token.consume(); 
          const auto T_val = Expr();
          token.consume();
          const auto F_val = Expr();
          return bool_val == 'T' ? static_cast<std::string>(T_val) : static_cast<std::string>(F_val);
        }
      }
    };
    return Expr();
  }
};
