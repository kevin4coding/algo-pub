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
  ListNode* sortList(ListNode* head) {
    struct {
      mutable ListNode* head_ll;
      mutable ListNode* head_rr;
      mutable ListNode* tail_ll;
      mutable ListNode* tail_rr;
    } ST;

    auto halve = [&]() {
      std::function<void(ListNode*, ListNode*)> fold = [&](ListNode* slow, ListNode* fast) {
        if (fast->next == nullptr or fast->next->next == nullptr) {
          ST.head_rr = slow->next;
          ST.head_ll = head;
          ST.tail_ll = slow;
          ST.tail_rr = fast->next == nullptr ? fast : fast->next;
          ST.tail_ll->next = nullptr;
          return;
        }
        else {
          fold(slow->next, fast->next->next);
        }
      };
      return fold(head, head);
    };

    std::function<ListNode*(ListNode*, ListNode*)> merge = [&](ListNode* h1, ListNode* h2) {
      if (h1 == nullptr or h2 == nullptr) {
        return h1 == nullptr ? h2 : h1;
      }
      else if (h1->val < h2->val) {
        h1->next = merge(h1->next, h2);
        return h1;
      }
      else {
        h2->next = merge(h1, h2->next);
        return h2;
      }
    };

    auto solve = [&] {
      if (head == nullptr or head->next == nullptr) {
        return head;
      }
      else {
        return halve(), merge(sortList(ST.head_ll), sortList(ST.head_rr));
      }
    };

    return solve();
  }
};
