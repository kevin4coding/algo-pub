class Solution {
 public:
  int snakesAndLadders(vector<vector<int>>& board) {
    const int N = std::size(board);
    
    auto get_coord = [&](int i) -> std::pair<int, int> {
      const int k = (i - 1) / N;
      if (k % 2 == 0) {
        return std::pair{N - 1 - k, (i - 1) % N};
      }
      else {
        return std::pair{N - 1 - k, N - 1 - ((i - 1) % N)};
      }
    };

    struct {
      mutable std::deque<int> Q = {};
      mutable std::optional<int> D[1000] = {};
    } ST;

    auto init_ST = [&]() {
      ST.Q.emplace_back(1);
      ST.D[1] = 0;
    };

    std::function<void(void)> bfs = [&, &Q = ST.Q, &D = ST.D]() {
      if (std::empty(Q) or D[N * N].has_value()) {
        return;
      }
      else {
        const auto curr_n = Q.front();
        Q.pop_front();
        for (int i = 1; i <= 6; ++i) {
          if (curr_n + i <= N * N) {
            const auto [r, c] = get_coord(curr_n + i);
            const auto next = board[r][c] == -1 ? curr_n + i : board[r][c];
            if (not D[next].has_value()) {
              D[next] = D[curr_n].value() + 1;
              Q.emplace_back(next);
            }
          }
        }          
        return bfs();
      }
    };

    return init_ST(), bfs(), ST.D[N * N].value_or(-1);
  }
};
