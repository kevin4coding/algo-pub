class Solution {
 public:
  ListNode* plusOne(ListNode* head) {
    std::function<int(ListNode*)> fold = [&](ListNode* n) { return !n ? 1 : ((n->val+= fold(n->next)) < 10) ? 0 : (std::exchange(n->val, 0), 1); };
    return !head ? nullptr : (fold(head) == 1 ? new ListNode(1, head) : head);
  }
};
