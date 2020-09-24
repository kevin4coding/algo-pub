class Solution {
 public:
  int minKnightMoves(int x, int y) {
    const int dr[8] = {1, -1, 2, -2, 1, -1, 2, -2};
    const int dc[8] = {2, 2, 1, 1, -2, -2, -1, -1};

    struct {
      mutable std::deque<std::pair<int, int>> Q = {};
      mutable std::unordered_map<int, std::unordered_map<int, std::optional<int>>> D = {};
    } ST;

    auto init_ST = [&]() {
      ST.Q.emplace_back(0, 0);
      ST.D[0][0] = 0;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q) or D[std::abs(x)][std::abs(y)].has_value()) {
        return;
      }
      else {
        const auto [r, c] = Q.front();
        Q.pop_front();
        for (int i = 0; i < 8; ++i) {
          const auto [nr, nc] = std::pair{r + dr[i], c + dc[i]};
          if (nr >= -1 and nc >= -1 and std::abs(nr) + std::abs(nc) <= 300 and not D[nr][nc].has_value()) {
            D[nr][nc] = D[r][c].value() + 1;
            Q.emplace_back(nr, nc);
          }
        }
        return bfs();
      }
    };

    return init_ST(), bfs(), ST.D[std::abs(x)][std::abs(y)].value();
  }
};
