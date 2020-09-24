class Solution {
 public:
  int countNodes(TreeNode* root) {
    const auto depth = [&]() {
      std::function<int(TreeNode*)> fold = [&](TreeNode* node) {
        return (node == nullptr) ? 0 : 1 + fold(node->left);
      };
      return fold(root);
    }();
    
    std::function<bool(TreeNode*, int, int, int)> check = [&](TreeNode* node, int ll, int rr, int idx) {
      if (ll + 1 == rr) {
        return node != nullptr;
      }
      else if (idx < (ll + rr) / 2) {
        return check(node->left, ll, (ll + rr) / 2, idx);
      }
      else {
        return check(node->right, (ll + rr) / 2, rr, idx);
      }
    };

    auto lower_boundary = [&](std::optional<int> self = {}) {
      std::function<void(int, int)> bsearch = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (check(root, 0, std::pow(2, depth - 1), mid) == true) {
          self.emplace(mid);
          bsearch(mid + 1, hi);
        }
        else {
          bsearch(lo, mid - 1);
        }
      };
      
      return bsearch(0, std::pow(2, depth - 1) - 1), self;
    };

    return root == nullptr ? 0 : std::pow(2, depth - 1) + lower_boundary().value();
  }
};
