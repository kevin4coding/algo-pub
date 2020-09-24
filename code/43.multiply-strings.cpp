class Solution {
 public:
  string multiply(string num1, string num2) {

    const int n1 = std::size(num1);
    const int n2 = std::size(num2);

    const auto prod_arr = [&](std::vector<int> self = {}) {
      self.resize(n2 + n1);
      for (int i = n1 - 1; i >= 0; --i) {
        for (int j = n2 - 1; j >= 0; --j) {
          const auto x = (num1[i] - '0') * (num2[j] - '0');
          self[i + j + 1] += x;
          self[i + j] += self[i + j + 1] / 10;
          self[i + j + 1] %= 10;
        }
      }
      std::reverse(std::begin(self), std::end(self));
      while (not std::empty(self) and self.back() == 0) self.pop_back();
      std::reverse(std::begin(self), std::end(self));
      return self;
    }();

    auto to_numchar = [&](int i) {
      return char(i + '0');
    };
    
    const auto solution = [&](std::string self = {}) {
      if (std::empty(prod_arr)) {
        self = "0";
      }
      else {      
        std::transform(std::begin(prod_arr), std::end(prod_arr), std::back_inserter(self), to_numchar);
      }
      return self;
    }();

    return solution;
    
  }
};
