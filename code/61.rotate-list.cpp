class Solution {
 public:
  ListNode* rotateRight(ListNode* head, int k) {
    std::function<int(ListNode*)> fold_L = [&](ListNode* n) {
      if (n == nullptr) {
        return 0;
      }
      else {
        return 1 + fold_L(n->next);
      }
    };

    std::function<ListNode*(ListNode*, int)> fold_nth = [&](ListNode* n, int k) {
      if (n == nullptr) {
        throw std::domain_error("");
      }
      else if (k == 0) {
        return n;
      }
      else {
        return fold_nth(n->next, k - 1);
      }
    };

    std::function<ListNode*(ListNode*)> fold_last = [&](ListNode* n) {
      if (n->next == nullptr) {
        return n;
      }
      else {
        return fold_last(n->next);
      }
    };

    const int N = fold_L(head);
    
    const auto solution = [&](){
      if (N == 0 or k % N == 0) {
        return head;
      }
      else {
        const int n = k % N;
        const auto head_R = fold_nth(head, N - n);
        const auto tail_L = fold_nth(head, N - n - 1);
        const auto tail_R = fold_last(head_R);
        tail_R->next = head;
        tail_L->next = nullptr;
        return head_R;
      }
    }();

    return solution;  
  }
};
