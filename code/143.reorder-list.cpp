class Solution {
 public:
  void reorderList(ListNode* head) {
    struct {
      mutable ListNode* head_ll;
      mutable ListNode* head_rr;
      mutable ListNode* tail_ll;
    } ST;

    const auto L = [&]() {
      std::function<int(ListNode*)> fold_L = [&](ListNode* n) {
        if (n == nullptr) {
          return 0;
        }
        else {
          return 1 + fold_L(n->next);
        }
      };
      return fold_L(head);
    }();

    std::function<ListNode*(ListNode*, int)> get = [&](ListNode* n, int id) {
      if (id == 0) {
        return n;
      }
      else {
        return get(n->next, id - 1);
      }
    };

    std::function<ListNode*(ListNode*, int, int)> reverse = [&](ListNode* n, int ll, int rr) {
      // helper method
      std::function<ListNode*(ListNode*, int)> fold_rev = [&, succ = (ListNode*) nullptr](ListNode* n ,int k) mutable {
        if (k == 0) {
          succ = n->next;
          return n;
        }
        else {
          ListNode* last = fold_rev(n->next, k - 1);
          n->next->next = n;
          n->next = succ;
          return last;
        }
      };

      if (ll == 0) {
        return fold_rev(n, rr);
      }
      else {
        n->next = reverse(n->next, ll - 1, rr - 1);
        return n;
      }
    };

    std::function<void(ListNode*, ListNode*)> merge = [&, tail = std::optional<ListNode*>{}](ListNode* h1, ListNode* h2) mutable {
      if (h1 == nullptr or h2 == nullptr) {
        return;
      }
      else {
        auto h1_next = h1->next;
        auto h2_next = h2->next;
        h1->next = h2;
        h2->next = h1_next;
        merge(h1_next, h2_next);
      }
    };


    auto solve = [&]() {
      if (L <= 2) {
        return;
      }
      else {
        reverse(head, L / 2 + 1, L - 1);
        ST.head_ll = head;
        ST.tail_ll = get(head, L / 2);
        ST.head_rr = get(head, L / 2 + 1);
        ST.tail_ll->next = nullptr;
        merge(ST.head_ll, ST.head_rr);
      }
    };

    solve();
    
  }
};
