class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    struct {
      mutable std::vector<std::string> acc = {};
      mutable std::string cache = {};
    } ST;
    
    std::function<void(int, int)> fold = [&, &acc = ST.acc, &cache = ST.cache](int open, int close) {
      if (open < close or open > n) {
        return;
      }
      else if (open == close and open == n) {
        acc.emplace_back(cache);
      }
      else {
        cache.push_back('(');
        fold(open + 1, close);
        cache.pop_back();
        cache.push_back(')');
        fold(open, close + 1);
        cache.pop_back();
      }
    };

    return fold(0, 0), ST.acc;
  }
};
