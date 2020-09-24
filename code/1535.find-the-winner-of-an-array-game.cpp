


class Solution {
 public:
  int getWinner(vector<int>& arr, int k) {
    const int n = std::size(arr); 

    auto simulate = [&, DQ = std::deque<int>(std::begin(arr), std::end(arr))]() mutable {
      std::function<int(int)> go = [&](int cnt) {
        if (cnt == k) {
          return DQ.front();
        }
        else {
          if (DQ[0] > DQ[1]) {
            const auto [q1, q2] = std::pair{DQ[0], DQ[1]};
            DQ.pop_front();
            DQ.pop_front();
            DQ.emplace_back(q2);
            DQ.emplace_front(q1);
            return go(++cnt);
          }
          else {
            DQ.emplace_back(DQ.front());
            DQ.pop_front();
            return go(1);
          }
        }
      };

      return go(0);
    };

    const auto solution = [&] {
      if (k > n) {
        return *std::max_element(std::begin(arr), std::end(arr));
      }
      else {
        return simulate();
      }
    }();

    return solution;
    
  }
};
