class Solution {
 public:
  bool isSubPath(ListNode* head, TreeNode* root) {
    std::function<bool(TreeNode*, ListNode*)> check = [&](TreeNode* ntree, ListNode* nlist) {
      if (ntree == nullptr and nlist!= nullptr) {
        return false;
      }
      else if (ntree->val != nlist->val) {
        return false;
      }
      else if (ntree->val == nlist->val and nlist->next == nullptr) {
        return true;
      }
      else {
        return check(ntree->left, nlist->next) or check(ntree->right, nlist->next);
      }
    };
    
    const auto solution = [&](bool acc = false) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr or acc == true) {
          return;
        }
        else {
          if (n->val == head->val) {
            acc |= check(n, head);
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    return solution;
  }
};
