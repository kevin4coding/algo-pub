class Solution {
 public:
  vector<string> letterCombinations(string digits) {
    const std::unordered_map<int, std::vector<char>> num_char_map = {{2, {'a', 'b', 'c'}},
                                                                     {3, {'d', 'e', 'f'}},
                                                                     {4, {'g', 'h', 'i'}},
                                                                     {5, {'j', 'k', 'l'}},
                                                                     {6, {'m', 'n', 'o'}},
                                                                     {7, {'p', 'q', 'r', 's'}},
                                                                     {8, {'t', 'u', 'v'}},
                                                                     {9, {'w', 'x', 'y', 'z'}}};
    struct {
      mutable std::vector<std::string> acc;
      mutable std::string cache = {};
    } ST;

    const int n = std::size(digits);

    std::function<void(int)> fold = [&](int i) {
      if (i == n) {
        if (not std::empty(ST.cache)) {
          ST.acc.emplace_back(ST.cache);
        }
        return;
      }
      else {
        for (const auto ch : num_char_map.at(digits[i] -  '0')) {
          ST.cache.push_back(ch);
          fold(i + 1);
          ST.cache.pop_back();
        }
      }
    };

    return fold(0), ST.acc;
  }
};
