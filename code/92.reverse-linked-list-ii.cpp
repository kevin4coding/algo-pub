/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode* reverseBetween(ListNode* head, int m, int n) {

    std::function<ListNode*(ListNode*, int)> fold = [&, succ = (ListNode*) nullptr](ListNode* n, int k) mutable {
      if (k == 1) {
        succ = n->next;
        return n;
      }
      else {
        ListNode* last = fold(n->next, k - 1);
        n->next->next = n;
        n->next = succ;
        return last;
      }
    };

    if (m == 1) {
      return fold(head, n);
    }
    else {
      head->next = reverseBetween(head->next, m - 1, n - 1);
      return head;
    }
  }
};
