class Solution {
 public:
  string intToRoman(int num) {
    
    std::function<std::string(int)> fold = [&](int n) {
      if (n >= 1000) {
        return "M" + fold(n - 1000);
      }
      else if (n >= 900) {
        return "CM" + fold(n - 900);
      }
      else if (n >= 500) {
        return "D" + fold(n - 500);
      }
      else if (n >= 400) {
        return "CD" + fold(n - 400);
      }
      else if (n >= 100) {
        return "C" + fold(n - 100);
      }
      else if (n >= 90) {
        return "XC" + fold(n - 90);
      }
      else if (n >= 50) {
        return "L" + fold(n - 50);
      }
      else if (n >= 40) {
        return "XL" + fold(n - 40);
      }
      else if (n >= 10) {
        return "X" + fold(n - 10);
      }
      else if (n >= 9) {
        return "IX" + fold(n - 9);
      }
      else if (n >= 5) {
        return "V" + fold(n - 5);
      }
      else if (n >= 4) {
        return "IV" + fold(n - 4);
      }
      else if (n >= 1) {
        return "I" + fold(n - 1);
      }
      else {
        return std::string{};
      }
    };

    return fold(num);
  }
};
