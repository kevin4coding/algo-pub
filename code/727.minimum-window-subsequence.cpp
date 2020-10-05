class Solution {
 public:
  string minWindow(string S, string T) {
    const int n_s = std::size(S);
    const int n_t = std::size(T);

    auto trim_from_right = [&](int i) {
      std::function<int(int, int)> fold = [&](int i, int id) {
        if (T[id] == S[i] and id == 0) {
          return i;
        }
        else if (T[id] == S[i] and id > 0) {
          return fold(i - 1, id - 1);
        }
        else {
          return fold(i - 1, id);
        }
      };
      return fold(i, n_t - 1);
    };

    auto solve = [&, acc_len = INT_MAX, acc_str = std::string{}]() mutable {
      for (auto [i, j] = std::pair{0, 0}; i < n_s; ) {
        if (S[i] == T[j]) {
          ++j;
        }
        if (j == n_t) {
          const int ll = trim_from_right(i);
          if (i - ll + 1 < acc_len) {
            acc_len = i - ll + 1;
            acc_str = std::string(std::begin(S) + ll, std::begin(S) + i + 1);
          }
          j = 0;
          i = ll + 1;
        }
        else {
          i++;
        }
      }
      return acc_str;
    };

    return solve();
  }
};

