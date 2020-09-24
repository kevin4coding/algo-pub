class Solution {
 public:
  int maxEnvelopes(vector<vector<int>>& envelopes) {
    const int n = std::size(envelopes);
    
    struct {
      mutable std::vector<std::vector<int>> pile = {};
    } ST;

    auto comp1 = [&](const std::vector<int>& x, const std::vector<int>& y) {
      if (x[0] < y[0]) {
        return true;
      }
      else if (x[0] > y[0]) {
        return false;
      }
      else {
        return x[1] >= y[1];
      }
    };

    auto comp2 = [&](const std::vector<int>& x, const std::vector<int> y) {
      return x[1] < y[1];
    };
    
    const auto sorted_envelopes = [&](std::vector<std::vector<int>> self = {}) {
      std::copy(std::begin(envelopes), std::end(envelopes), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self), comp1);
      return self;
    }();

    std::function<void(int)> fold = [&](int i) {
      if (i == n) {
        return;
      }
      else {
        const auto llmost = std::lower_bound(std::begin(ST.pile), std::end(ST.pile), sorted_envelopes[i], comp2);
        if (llmost == std::end(ST.pile)) {
          ST.pile.emplace_back(sorted_envelopes[i]);
        }
        else {
          std::exchange(*llmost, sorted_envelopes[i]);
        }
        return fold(i + 1);
      }
    };

    return fold(0), std::size(ST.pile);
    
  }
};
