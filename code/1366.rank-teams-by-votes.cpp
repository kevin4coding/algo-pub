class Solution {
 public:
  string rankTeams(vector<string>& votes) {
    const int n = std::size(votes[0]);
    
    const auto rankings = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(26, std::vector<int>(n, 0));
      for (const auto &vote : votes) {
        for (int i = 0; i < n; ++i) {
          ++self[vote[i] - 'A'][i];
        }
      }
      return self;
    }();


    const auto solution = [&](std::string self = {}) {
      std::copy(std::begin(votes[0]), std::end(votes[0]), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self), [&](char c1, char c2) {
        if (rankings[c1 - 'A'] == rankings[c2 - 'A']) {
          return c1 < c2;
        }
        else {
          return rankings[c1 - 'A'] > rankings[c2 - 'A'];
        }
      });

      return self;
    }();

    return solution;
  }
};
