class Solution {
 public:
  vector<int> plusOne(vector<int>& digits) {
    const int n = std::size(digits);
    
    std::function<std::vector<int>(int)> f = [&, D = digits, carry = 0](int i) mutable {
      if (i == 0) {
        if (carry == 1 or n == 1) {
          D[i] = (D[i] + 1) % 10;
          if (D[i] == 0)
            D.insert(std::begin(D), 1);
        }
        return D;
      }
      else if (i == n - 1) {
        D[i] = (D[i] + 1) % 10;
        carry = int(D[i] == 0);        
        return f(i - 1);
      }
      else if (i > 0 and i < n - 1 and carry == 0) {
        return D;
      }
      else if (i > 0 and i < n - 1 and carry == 1) {
        D[i] = (D[i] + 1) % 10;
        carry = int(D[i] == 0);
        return f(i - 1);
      }
      else throw std::domain_error("unmatched case");
    };

    return f(n - 1);
  }
};
