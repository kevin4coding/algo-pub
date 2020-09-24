class Solution {
 public:
  bool isValid(string s) {
    const int n = std::size(s);
    
    struct {
      mutable std::deque<int> DQ = {};
      mutable bool valid = true;
    } ST;

    auto is_open = [](char ch) { return ch == '(' or ch == '[' or ch == '{'; };

    auto lhs = [](char ch) {
      if (ch == ')') {
        return '(';
      }
      else if (ch == ']') {
        return '[';
      }
      else if (ch == '}') {
        return '{';
      }
      throw std::domain_error("");
    };
    
    std::function<void(int)> fold = [&](int i) {
      if (i == n) {
        ST.valid = std::empty(ST.DQ);
      }
      else if (is_open(s[i])) {
        return (ST.DQ.emplace_back(s[i]), fold(i + 1));
      }
      else {
        if (std::empty(ST.DQ) or ST.DQ.back() != lhs(s[i])) {
          return void(std::exchange(ST.valid, false));
        }
        else {
          return (ST.DQ.pop_back(), fold(i + 1));
        }
      }
    };

    return fold(0), ST.valid;
  }
};
