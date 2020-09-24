class Solution {
 public:
  TreeNode* sortedListToBST(ListNode* head) {
    std::function<int(ListNode*)> fold = [&](ListNode* n) {
      if (n == nullptr) {
        return 0;
      }
      else {
        return 1 + fold(n->next);
      }
    };

    const auto N = fold(head);
    
    std::function<TreeNode*(int, int)> build = [&, lhead = head](int ll, int rr) mutable {
      if (ll > rr) {
        return static_cast<TreeNode*>(nullptr);
      }
      else {
        const int mid = ll + (rr - ll) / 2;
        const auto ltree = build(ll, mid - 1);
        auto result = new TreeNode(std::exchange(lhead, lhead->next)->val);
        const auto rtree = build(mid + 1, rr);
        std::exchange(result->left, ltree);
        std::exchange(result->right, rtree);
        return result;
      }
    };

    return build(0, N - 1);
  }
};
