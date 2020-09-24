class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    std::function<int(ListNode*)> fold_L = [&](ListNode* n) {
      return n == nullptr ? 0 : 1 + fold_L(n->next);
    };

    int N1 = fold_L(l1);
    int N2 = fold_L(l2);

    if (N1 < N2) {
      std::swap(l1, l2);
      std::swap(N1, N2);
    }
    
    std::function<std::pair<ListNode*, int>(ListNode*, int, ListNode*, int)> fold = [&](ListNode* n1, int id1, ListNode* n2, int id2) {
      if (n1 == nullptr and n2 == nullptr) {
        return std::pair{static_cast<ListNode*>(nullptr), 0};
      }
      else if (id1 > id2) {
        const auto [n, carry] = fold(n1->next, id1 - 1, n2, id2);
        if (n1->val + carry == 10) {
          if (n1 == l1 and n2 == l2) {
            return std::pair{new ListNode{1, new ListNode(0, n)}, 0};
          }
          else {
            return std::pair{new ListNode(0, n), 1};
          }
        }
        else  {
          return std::pair{new ListNode(n1->val + carry, n), 0};
        }
      }
      else {
        const auto [n, carry] = fold(n1->next, id1 - 1, n2->next, id2 - 1);
        if (n1->val + n2->val + carry >= 10) {
          if (n1 == l1 and n2 == l2) {
            return std::pair{new ListNode(1, new ListNode((n1->val + n2->val + carry) % 10, n)), 0};
          }
          else {
            return std::pair{new ListNode((n1->val + n2->val + carry) % 10, n), 1};
          }
        }
        else {
          return std::pair{new ListNode(n1->val + n2->val + carry, n), 0};
        }
      }
    };


    return fold(l1, N1, l2, N2).first;
  }
};

