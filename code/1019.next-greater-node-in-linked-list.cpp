class Solution {
 public:
  vector<int> nextLargerNodes(ListNode* head) {
    const auto arr = [&](std::vector<int> self = {}) {
      std::function<void(ListNode*)> fold = [&](ListNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          self.emplace_back(n->val);
          fold(n->next);
        }
      };
      return fold(head), self;
    }();

    const int n = std::size(arr);
    
    const auto NGE = [&, DQ = std::deque<int>{}](std::vector<std::optional<int>> self = {}) mutable {
      self.resize(std::size(arr), std::optional<int>{});
      for (int i = n - 1; i >= 0; --i) {
        while (not std::empty(DQ) and DQ.front() <= arr[i]) {
          DQ.pop_front();
        }
        if (not std::empty(DQ)) {
          self[i] = DQ.front();
        }
        DQ.emplace_front(arr[i]);
      }
      return self;      
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      std::transform(std::begin(NGE), std::end(NGE), std::back_inserter(self), [&](const auto &x) {
        return x.value_or(0);
      });
      return self;
    }();

    return solution;
  }
};
