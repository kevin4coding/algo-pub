class Solution {
 public:
  int findMinMoves(vector<int>& machines) {
    const int n = std::size(machines);
    const auto total = std::accumulate(std::begin(machines), std::end(machines), 0);
    if (total % n != 0) {
      return -1;
    }
    if (n == 1) {
      return 0;
    }

    const auto avg = total / n;

    const auto prefix_sum = [&, self = std::vector<int>(n)]() mutable {
      for (int i = 0; i < n; ++i) {
        self[i] = (i == 0) ? machines[i] : self[i - 1] + machines[i];
      }
      return self;
    }();

    auto RMQ = [&](int i, int j) {
      if (i == 0) {
        return prefix_sum[j];
      }
      else {
        return prefix_sum[j] - prefix_sum[i - 1];
      }
    };

    const auto suffix_sum = [&, self = std::vector<int>(n)]() mutable  {
      for (int i = n - 1; i >= 0; --i) {
        self[i] = (i == n - 1) ? machines[i] : self[i + 1] + machines[i];
      }
      return self;
    }();

    const auto total_move = [&, self = std::vector<int>(n)]() mutable {
      for (int i = 0; i < n; ++i) {
        if (i == 0) {
          const int ll2rr = std::max(0, (n - (i + 1)) * avg - RMQ(i + 1, n - 1));
          self[i] = ll2rr;
        }
        else if (i == n - 1) {
          const int rr2ll = std::max(0, i * avg - RMQ(0, i - 1));
          self[i] = rr2ll;
        }
        else {
          const int rr2ll = std::max(0, i * avg - RMQ(0, i - 1));
          const int ll2rr = std::max(0, (n - (i + 1)) * avg - RMQ(i + 1, n - 1));
          self[i] = (rr2ll + ll2rr);
        }
      }
      return self;
    }();

    auto solve = [&](int acc = INT_MIN) {
      for (int i = 0; i < n; ++i) {
        acc = std::max(total_move[i], acc);
      }
      return acc;
    };

    return solve();
  }
};
