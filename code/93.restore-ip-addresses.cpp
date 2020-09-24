class Solution {
 public:
  vector<string> restoreIpAddresses(string s) {

    const int n = std::size(s);
    
    struct {
      mutable std::vector<std::string> acc = {};
      mutable std::vector<int> cache = {};
    } ST;


    auto make_ip = [&](const std::vector<int>& arr) {
      auto acc = std::string{};
      for (int i = 0; i < 4; ++i) {
        acc += std::to_string(arr[i]);
        if (i != 3) acc.push_back('.');
      }
      return acc;
    };
    
    std::function<void(int, int)> fold = [&](int i, int cnt) {
      if (cnt == 4) {
        if (i == n and 0 <= ST.cache.back() and ST.cache.back() <= 255) {
          // emplace
          ST.acc.emplace_back(make_ip(ST.cache));
          return;
        }
      }
      else {
        if (s[i] == '0') {
          ST.cache.emplace_back(0);
          fold(i + 1, cnt + 1);
          ST.cache.pop_back();
        }
        else {
          for (auto [k, acc] = std::pair{i, 0}; k < n and acc <= 255; ++k) {
            acc = 10 * acc + s[k] - '0';
            if (acc <= 255) {
              ST.cache.emplace_back(acc);
              fold(k + 1, cnt + 1);
              ST.cache.pop_back();
            }
          }
        }
      }
    };

    return fold(0, 0), ST.acc;
  }
};
