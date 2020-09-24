class Solution {
 public:
  bool hasValidPath(vector<vector<int>>& grid) {
    const int R = std::size(grid);
    const int C = std::size(grid[0]);

    const auto dirs = std::unordered_map<char, std::pair<int, int>>{{'r', {0, 1}},
                                                                    {'l', {0, -1}},
                                                                    {'u', {-1, 0}},
                                                                    {'d', {1, 0}}};

    const struct {
      mutable bool vis[300][300] = {};
      mutable bool reach = false;
    } ST;

    auto inbound = [&](int r, int c) {
      return 0 <= r and r < R and 0 <= c and c < C;
    };
    
    auto match = [&](int i, int j, char dir) {
      if (i == 1) {
        if (dir == 'r') {
          return j == 1 or j == 3 or j == 5;
        }
        else if (dir == 'l') {
          return j == 1 or j == 4 or j == 6;
        }
        else {
          return false;
        }
      }
      else if (i == 2) {
        if (dir == 'u') {
          return j == 2 or j == 3 or j == 4;
        }
        else if (dir == 'd') {
          return j == 2 or j == 5 or j == 6;
        }
        else {
          return false;
        }
      }
      else if (i == 3) {
        if (dir == 'l') {
          return j == 1 or j == 4 or j == 6;
        }
        else if (dir == 'd') {
          return j == 2 or j == 5 or j == 6;
        }
        else {
          return false;
        }
      }
      else if (i == 4) {
        if (dir == 'r') {
          return j == 1 or j == 3 or j == 5;
        }
        else if (dir == 'd') {
          return j == 2 or j == 5 or j == 6;
        }
        else {
          return false;
        }
      }
      else if (i == 5) {
        if (dir == 'u') {
          return j == 2 or j == 3 or j == 4;
        }
        else if (dir == 'l') {
          return j == 1 or j == 4 or j == 6;
        }
        else {
          return false;
        }
      }
      else if (i == 6) {
        if (dir == 'u') {
          return j == 2 or j == 3 or j == 4;
        }
        else if (dir == 'r') {
          return j == 1 or j == 3 or j == 5;
        }
        else {
          return false;
        }
      }
      else throw std::domain_error("");
    };

    std::function<void(int, int)> fold = [&](int r, int c) {
      ST.vis[r][c] = true;
      if (r == R - 1 and c == C - 1) {
        ST.reach = true;
      }
      for (const auto & [dir, rc] : dirs) {
        const auto [dr, dc] = rc;
        const auto [nr, nc] = std::pair{r + dr, c + dc};
        if (inbound(nr, nc) and not ST.vis[nr][nc] and match(grid[r][c], grid[nr][nc], dir)) {
          fold(nr, nc);
        }
      }
    };

    return (fold(0, 0), ST.reach);
  }
};
