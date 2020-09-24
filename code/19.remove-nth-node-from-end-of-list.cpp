class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {

    std::function<int(ListNode*)> fold_L = [&](ListNode* node) {
      if (node == nullptr) {
        return 0;
      }
      else {
        return 1 + fold_L(node->next);
      }
    };

    const auto L = fold_L(head);

    std::function<void(std::optional<ListNode*>, ListNode*, int)> fold = [&](std::optional<ListNode*> prev, ListNode* curr_n, int i) {
      if (curr_n == nullptr) {
        return;
      }
      else if (i == L - n) {
        if (curr_n == head) {
          const auto head_copy = head;
          std::exchange(head, head->next);
          delete head_copy;
        }
        else {
          (prev.value())->next = curr_n->next;
          delete curr_n;
        }
      }
      else {
        fold(curr_n, curr_n->next, i + 1);
      }
    };

    return fold(std::optional<ListNode*>{}, head, 0), head;
  }
};
