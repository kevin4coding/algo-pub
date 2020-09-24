class Solution {
 public:
  ListNode* removeZeroSumSublists(ListNode* head) {
    head = new ListNode(0, head); // dummify
    
    const auto prefix_map = [&](std::unordered_map<int, ListNode*> self = {}) {
      std::function<void(ListNode*)> fold = [&, acc = 0](ListNode* n) mutable {
        if (n == nullptr) {
          return;
        }
        self[acc += n->val] = n;
        fold(n->next);
      };
      return fold(head), self;
    }();

    std::function<ListNode*(ListNode*)> fold = [&, acc = 0](ListNode* n) mutable {
      if (n == nullptr) {
        delete std::exchange(head, head->next); // memory safe 
        return static_cast<ListNode*>(nullptr);
      }
      else {
        return new ListNode(n->val, fold(prefix_map.at(acc += n->val)->next));
      }
    };

    return fold(head)->next;
  }
};
