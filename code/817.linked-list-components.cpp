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
  int numComponents(ListNode* head, vector<int>& G) {
    struct { 
      mutable std::unordered_set<int> G_set = {};
      mutable int cc_cnt = 0;
    } ST;

    auto init_ST = [&]() {
      std::copy(std::begin(G), std::end(G), std::inserter(ST.G_set, std::begin(ST.G_set)));
    };

    std::function<void(ListNode*)> fold_vis = [&](ListNode* n) {
      if (n == nullptr or not ST.G_set.count(n->val)) {
        return;
      }
      else {
        ST.G_set.erase(n->val);
        fold_vis(n->next);
      }
    };

    std::function<void(ListNode*)> fold_cnt = [&](ListNode* n) {
      if (n == nullptr) {
        return;
      }
      else {   
        if (ST.G_set.count(n->val)) {
          ++ST.cc_cnt;
          fold_vis(n);
        }
        fold_cnt(n->next);
      }
    };

    return (init_ST(), fold_cnt(head), ST.cc_cnt);
  }
};
