class Solution {
 public:
  ListNode* partition(ListNode* head, int x) {
    struct {
      mutable ListNode* head_ll = nullptr;
      mutable ListNode* head_rr = nullptr;
      mutable ListNode* tail_ll = nullptr;
      mutable ListNode* tail_rr = nullptr;
      mutable ListNode* final_head = nullptr;

      void push_ll(int i) {
        if (head_ll == nullptr) {
          head_ll = new ListNode(i);
          tail_ll = head_ll;
        }
        else {
          tail_ll->next = new ListNode(i);
          tail_ll = tail_ll->next;
        }
      }

      void push_rr(int i) {
        if (head_rr == nullptr) {
          head_rr = new ListNode(i);
          tail_rr = head_rr;
        }
        else {
          tail_rr->next = new ListNode(i);
          tail_rr = tail_rr->next;
        }
      }
    } ST;

    std::function<void(ListNode*)> fold = [&](ListNode* n) {
      if (n == nullptr) {
        // combine the two lists
        if (ST.tail_ll != nullptr) {
          ST.tail_ll->next = ST.head_rr;
          ST.final_head = ST.head_ll;
        }
        else {
          ST.final_head = ST.head_rr;
        }
        return;
      }
      else {
        if (n->val < x) {
          ST.push_ll(n->val);
        }
        else if (n->val >= x) {
          ST.push_rr(n->val);
        }
        fold(n->next);
      }
    };


    return fold(head), ST.final_head;
    
  }
};
