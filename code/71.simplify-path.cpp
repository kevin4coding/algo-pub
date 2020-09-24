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
  string simplifyPath(string path) {
    auto token = basic_tokenizer(path);

    struct {
      mutable std::vector<std::string> acc;
    } ST;


    auto get_next_dir = [&]() {
      auto acc = std::string{};
      while (token.has_next() and token.peek() != '/') acc.push_back(token.next<char>());
      return acc;
    };

    std::function<void(void)> fold = [&]() {
      if (not token.has_next()) {
        return;
      }
      else {
        // this whole 3 lines could be packed into a nice procedure. but mehh..
        while (token.peek() == '/') token.consume();
        if (not token.has_next()) return;
        const auto next_dir = get_next_dir();
        if (next_dir == ".") {
          return fold();
        }
        else if (next_dir == "..") {
          if (not std::empty(ST.acc)) {
            ST.acc.pop_back();
          }
          return fold();
        }
        else {
          ST.acc.emplace_back(next_dir);
          return fold();
        }
      }
    };

    const auto solution = [&](std::string self = "/") {
      fold();
      for (int i = 0; i < std::size(ST.acc); ++i) {
        self += (ST.acc[i] + (i == std::size(ST.acc) - 1 ? "" : "/"));
      }
      return self;
    }();
    return solution;
  }
};
