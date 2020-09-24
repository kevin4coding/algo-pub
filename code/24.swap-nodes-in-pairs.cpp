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
  ListNode* swapPairs(ListNode* head) {
    std::function<ListNode*(ListNode*)> fold = [&](ListNode* n) {
      if (n == nullptr or n->next == nullptr) {
        return n;
      }
      else {
        const auto [fst, snd] = std::pair{n, n->next};
        fst->next = fold(snd->next);
        snd->next = fst;
        return snd;
      }
    };

    return fold(head);
  }
};
