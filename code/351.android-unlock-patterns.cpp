class Solution {
 public:
  int numberOfPatterns(int m, int n) {
    const auto blocks = [&](std::vector<std::vector<std::optional<int>>> self = {}) {
      self.resize(10, std::vector<std::optional<int>>(10, std::optional<int>{}));
      self[1][9] = 5; self[1][3] = 2; self[1][7] = 4;
      self[2][8] = 5;
      self[3][1] = 2; self[3][7] = 5; self[3][9] = 6;
      self[4][6] = 5;
      self[6][4] = 5;
      self[7][1] = 4; self[7][3] = 5; self[7][9] = 8;
      self[8][2] = 5;
      self[9][7] = 8; self[9][3] = 6; self[9][1] = 5;
      return self;
    }();

    struct {
      mutable bool vis[11] = {};
      mutable int acc = 0;
    } ST;


    std::function<void(int, int)> fold = [&](int n, int remain) {
      if (remain == 1) {
        ST.acc++;
        return;
      }
      else {
        ST.vis[n] = true;
        for (int i = 1; i <= 9; ++i) {
          if (not ST.vis[i] and (not blocks[n][i].has_value() or ST.vis[blocks[n][i].value()] == true)) {
            fold(i, remain - 1);
          }
        }
        ST.vis[n] = false;
      };
    };

    auto solve = [&]() {
      for (int i = 1; i <= 9; ++i) {
        for (int k = m; k <= n; ++k) {
          fold(i, k);
        }
      }
      return ST.acc;
    };

    return solve();
  }
};
