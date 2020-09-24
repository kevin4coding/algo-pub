class Solution {
 public:
  vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {

    auto filter = [&](const std::vector<int> & r) {
      if (veganFriendly) {
        return r[2] == veganFriendly and r[3] <= maxPrice and r[4] <= maxDistance;
      }
      else {
        return r[3] <= maxPrice and r[4] <= maxDistance;
      }
    };

    auto sorter = [&](const std::vector<int> &r1, std::vector<int> &r2) {
      if (r1[1] == r2[1]) {
        return r1[0] > r2[0];
      }
      else {
        return r1[1] > r2[1];
      }
    };    

    const auto candidate = [&](std::vector<std::vector<int>> self = {}) {
      std::copy_if(std::begin(restaurants), std::end(restaurants), std::back_inserter(self), filter);
      std::sort(std::begin(self), std::end(self), sorter);
      return self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      std::transform(std::begin(candidate), std::end(candidate), std::back_inserter(self), [&](const auto &x) {
        return x[0];
      });
      return self;
    }();


    return solution;
  }
};
