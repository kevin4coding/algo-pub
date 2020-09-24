class Solution {
 public:
  ListNode* insertionSortList(ListNode* head) {

    std::function<std::optional<ListNode*>(ListNode*, int)> find_pivot = [&](ListNode* n, int val) {
      if (n->next == nullptr) {
        return std::make_optional(n);
      }
      else if (n->next->val >= val) {
        return std::make_optional(n);
      }
      else {
        return find_pivot(n->next, val);
      }
    };

    
    std::function<ListNode*(ListNode*)> fold = [&](ListNode* n) {
      if (n == nullptr or n->next == nullptr) {
        return n;
      }
      else {
        const auto sorted_head = fold(n->next);
        if (sorted_head->val >= n->val) {
          n->next = sorted_head;
          return n;
        }
        else {
          const auto pivot = find_pivot(sorted_head, n->val).value();
          n->next = pivot->next;
          pivot->next = n;
          return sorted_head;
        }
      }
    };

    return fold(head);
  }
};








