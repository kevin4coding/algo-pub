class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    std::function<ListNode*(ListNode*)> fold = [&](ListNode* n) {
      if (n == nullptr or n->next == nullptr) {
        return n;
      }
      else {
        auto result = fold(n->next);
        n->next->next = n;
        n->next = nullptr;
        return result;
      }
    };
    return fold(head);
  }
};
