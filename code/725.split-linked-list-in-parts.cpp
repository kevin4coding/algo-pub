class Solution {
 public:
  vector<ListNode*> splitListToParts(ListNode* root, int k) {
    struct group_t {
      ListNode* head;
      ListNode* tail;
      int max_capacity;
      int capacity;
    };

    struct {
      mutable std::unordered_map<int, group_t> group;
      mutable int curr_gid = 0;

      void push(ListNode* n) {
        auto& [head, tail, max_capacity, capacity] = group[curr_gid];
        if (++capacity == max_capacity) {
          ++curr_gid;
        }
        if (head == nullptr) {
          head = n;
          tail = n;
        }
        else {
          tail->next = n;
          tail = tail->next;
        }
      }
    } ST;

    const int N = [&]() {
      std::function<int(ListNode*)> fold_L = [&](ListNode* n) {
        return n == nullptr ? 0 : 1 + fold_L(n->next);
      };
      return fold_L(root);
    }();

    auto init_ST = [&]() {
      if (k >= N) {
        for (int i = 0; i < k; ++i) {
          ST.group.emplace(i, group_t{nullptr, nullptr, 1, 0});
        }
      }
      else {
        for (int i = 0; i < k; ++i) {
          ST.group.emplace(i, group_t{nullptr, nullptr, N / k, 0});
        }
        for (int i = 0; i < N % k; ++i) {
          ++ST.group[i].max_capacity;
        }
      }
    };
      
    std::function<void(int, ListNode*)> fold = [&](int i, ListNode* n) {
      return i == N ? std::void_t<>() : (ST.push(n), fold(i + 1, n->next));
    };

    const auto solution = [&](std::vector<ListNode*> self = {}) {
      init_ST();
      fold(0, root);
      self.resize(k);
      for (const auto [gid, group] : ST.group) {
        const auto [head, tail, _1, _2] = group;
        if (head != nullptr and tail != nullptr) {
          tail->next = nullptr;
          self[gid] = head;
        }
      }
      return self;
    }();

    return solution;
  }
};
