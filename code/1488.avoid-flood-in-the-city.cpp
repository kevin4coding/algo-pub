class Solution {
 public:
  vector<int> avoidFlood(vector<int>& rains) {
    const int n = std::size(rains);
     
    const auto time_record = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      for (int i = 0; i < n; ++i) {
        if (rains[i] != 0) {
          self[rains[i]].emplace_back(i);
        }
      }

      for (auto & [_, time] : self) {
        std::reverse(std::begin(time), std::end(time));
      }
      
      return self;
    }();

    auto make_zeros = [&](std::set<int> self = {}) {
      for (int i = 0; i < n; ++i) {
        if (rains[i] == 0) {
          self.emplace(i);
        }
      }
      return self;
    };

    const auto solution = [&, zeros = make_zeros()](std::optional<std::vector<int>> self = {}) mutable {
      self.emplace(std::vector<int>(n, 1));
      for (int i = 0; i < n and self.has_value(); ++i) {
        if (rains[i] == 0) {
          continue;
        }
        else if (const auto last = std::upper_bound(std::begin(time_record.at(rains[i])),
                                                    std::end(time_record.at(rains[i])),
                                                    i,
                                                    std::greater<int>()); last == std::end(time_record.at(rains[i]))) {
          self.value()[i] = -1;
        }
        else if (last != std::end(time_record.at(rains[i]))) {
          const auto to_dry = zeros.upper_bound(*last);
          self.value()[i] = -1;
          if (to_dry == std::end(zeros) or *to_dry >= i) {
            self.reset();
          }
          else {
            self.value()[*to_dry] = rains[i];
            zeros.erase(*to_dry);
          }
        }
      }
      return self;
    }();

    return solution.value_or(std::vector<int>{});
    
  }
};

