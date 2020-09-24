class Solution {
 public:
  int myAtoi(string str) {
    
    const int n = std::size(str);
    
    struct {
      mutable int acc = 0;
      mutable bool overflow_l = false;
      mutable bool overflow_u = false;
      mutable bool negative = false;
      mutable bool invalid = false;
      mutable bool met_number = false;
      mutable bool met_others = false;
      mutable bool met_space = false;
      mutable bool met_sign = false;
    } ST;


    // fold with states
    std::function<void(int)> fold = [&](int i) {
      if (i == n) {
        return;
      }
      else if (str[i] == '-' or str[i] == '+') {
        if (not ST.met_sign) {
          return ST.met_number ? std::void_t<>() : (std::exchange(ST.negative, str[i] == '-'),
                                                    std::exchange(ST.met_sign, true),
                                                    fold(i + 1));
        }
        else {
          return ST.met_number ? std::void_t<>() : (std::exchange(ST.invalid, true), std::void_t<>());
        }
      }
      else if (std::isdigit(str[i])) {
        if (ST.met_others) {
          return;
        }
        else {
          // could do a more modularized design to increase readability. But mehhh..
          const auto next = [&]() {
            if (not ST.met_number) {
              ST.met_number = true;
              return ST.negative ? (-1) * (ST.acc * 10 + str[i] - '0') : (ST.acc * 10 + str[i] - '0');
            }
            else if (ST.negative) {
              if (ST.acc < INT_MIN / 10 or (ST.acc < 0 and ST.acc * 10 - INT_MIN  <= (str[i] - '0'))) {
                return (int) std::exchange(ST.overflow_l, true);
              }
              else {
                return ST.acc * 10 - (str[i] - '0');
              }
            }
            else {
              if (ST.acc > INT_MAX / 10 or INT_MAX - ST.acc * 10 <= str[i] - '0') {
                return (int) std::exchange(ST.overflow_u, true);
              }
              else {
                return ST.acc * 10 + (str[i] - '0');
              }
            }
          }();
          return (ST.overflow_u or ST.overflow_l) ? std::void_t<>() : (std::exchange(ST.acc, next), fold(i + 1));
        }
      }
      else if (str[i] == ' ') {
        return (not ST.met_number and not ST.met_sign) ? fold(i + 1) : std::void_t<>();
      }
      else if (not std::isdigit(str[i])) {
        if (not ST.met_number) {
          return std::exchange(ST.invalid, true), std::void_t<>();
        }
        else {
          return std::exchange(ST.met_others, true), fold(i + 1);
        }
      }
    };

    auto solve = [&]() {
      fold(0);
      if (ST.invalid) {
        return 0;
      }
      else if (ST.overflow_u) {
        return INT_MAX;
      }
      else if (ST.overflow_l) {
        return INT_MIN;
      }
      else {
        return ST.acc;
      }
    };

    return solve();
  }
};
