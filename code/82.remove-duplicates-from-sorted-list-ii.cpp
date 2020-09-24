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
    ListNode* deleteDuplicates(ListNode* head) {
      std::function<ListNode*(ListNode*)> next = [&](ListNode* n) {
        if (next == nullptr or n->next == nullptr) {
          return (ListNode*) nullptr;
        }
        else if (n->next->val == n->val) {
          return next(n->next);
        }
        else if (n->next->val != n->val) {
          return n->next;
        }
        else throw std::domain_error("unmatched case");
          
      };
      
      std::function<ListNode*(ListNode*)> fold = [&](ListNode* n) {
        if (n == nullptr or n->next == nullptr) {
          return n;
        }
        else if (n->next->val == n->val) {
          return fold(next(n));
        }
        else {
          return new ListNode(n->val, fold(n->next));
        }
      };

      return fold(head);
    }
};
