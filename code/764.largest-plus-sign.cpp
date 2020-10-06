static struct {
  mutable std::optional<int> f[500][500][4];
  mutable int grid[500][500];

  void reset(int r, int c, int l) {
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        grid[i][j] = 1;
        for (int k = 0; k < l; ++k) {
          f[i][j][k].reset();
        }
      }
    }
  }
} mempool;

auto memo = mempool.f;
auto grid = mempool.grid;

const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};    
int R, C;

bool inbound(int r, int c) {
  return 0 <= r and r < R and 0 <= c and c < C;
};

// shitty OJ judging system. Should be inside.
int f(int i, int j, int k) {
  if (memo[i][j][k].has_value()) {
    return memo[i][j][k].value();
  }
  else {
    return memo[i][j][k].emplace([&] {
      if (grid[i][j] == 0) {
        return 0;
      }
      else if (grid[i][j] == 1 and inbound(i + dr[k], j + dc[k])) {
        return 1 + f(i + dr[k], j + dc[k], k);
      }
      else if (grid[i][j] == 1 and not inbound(i + dr[k], j + dc[k])) {
        return 1;
      }
      else throw;
    }());
  }
};


class Solution {
 public:
  int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
    mempool.reset(N, N, 4);

    for (const auto & m : mines) {
      const auto [r, c] = std::pair{m[0], m[1]};
      mempool.grid[r][c] = 0;
    }
    
    R = N; C = N;

    auto plus_size = [&](int r, int c) {
      return std::min({f(r, c, 0), f(r, c, 1), f(r, c, 2), f(r, c, 3)});
    };

    auto solve = [&](int acc = 0) {
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          if (mempool.grid[r][c] == 1) {
            acc = std::max(acc, plus_size(r, c));
            if (acc > std::max(R - r, C - c)) break; // prune
          }
        }
      }
      return acc;
    };

    return solve();
  }
};
