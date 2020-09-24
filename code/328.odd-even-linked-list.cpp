class Solution {
 public:
  ListNode* oddEvenList(ListNode* head) {
    struct {
      mutable ListNode* head_odd = nullptr;
      mutable ListNode* head_even = nullptr;
      mutable ListNode* tail_odd = nullptr;
      mutable ListNode* tail_even = nullptr;

      void push_odd(ListNode* n) {
        if (head_odd == nullptr) {
          head_odd = n;
          tail_odd = n;
        }
        else {
          tail_odd->next = n;
          tail_odd = tail_odd->next;
        }
      }

      void push_even(ListNode *n) {
        if (head_even == nullptr) {
          head_even = n;
          tail_even = n;
        }
        else {
          tail_even->next = n;
          tail_even = tail_even->next;
        }
      }
    } ST;

    const int L = [&]() {
      std::function<int(ListNode*)> fold = [&](ListNode* n) {
        return n == nullptr ? 0 : 1 + fold(n->next);
      };
      return fold(head);
    }();

    std::function<void(int, ListNode*)> group = [&](int i, ListNode* n) {
      if (i == L + 1) {
        return;
      }
      else if (i % 2 == 1) {
        ST.push_odd(n);
        return group(i + 1, n->next);
      }
      else {
        ST.push_even(n);
        return group(i + 1, n->next);
      }
    };

    const auto solution = [&]() {
      if (head == nullptr or head->next == nullptr) {
        return head;
      }
      else {
        group(1, head);
        std::exchange(ST.tail_odd->next, ST.head_even);
        std::exchange(ST.tail_even->next, nullptr);
        return ST.head_odd;
      }
    }();

    return solution;
  }
};
