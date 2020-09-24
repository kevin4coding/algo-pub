class Solution {
 public:
  int depthSumInverse(vector<NestedInteger>& nestedList) {

    std::function<int(const NestedInteger&)> fold_depth = [&](const NestedInteger& n) {
      if (n.isInteger()) {
        return 1;
      }
      else {
        return [&](int acc = INT_MIN) {
          for (const auto & l : n.getList()) {
            acc = std::max(acc, 1 + fold_depth(l));
          }
          return acc;
        }();
      }
    };

    std::function<int(const NestedInteger&, int)> fold_sum = [&](const NestedInteger& n, int level) {
      if (n.isInteger()) {
        return n.getInteger() * level;
      }
      else {
        return [&](int acc = 0) {
          for (const auto & l : n.getList()) {
            acc += fold_sum(l, level - 1);
          }
          return acc;
        }();
      }
    };

    const auto D = [&](int self = INT_MIN) {
      for (const auto & l : nestedList) {
        self = std::max(self, fold_depth(l));
      }
      return self;
    }();
    
    const auto solution = [&](int acc = 0) {
      for (const auto & l : nestedList) {
        acc += fold_sum(l, D);
      }
      return acc;
    }();

    return solution;
  }
};
