class Solution {
 public: 
  bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    auto is_leaf = [&](TreeNode* n) {
      return n->left == nullptr and n->right == nullptr;
    };
        
    std::function<bool(TreeNode*, TreeNode*)> f = [&](TreeNode* n1, TreeNode *n2) {
      if (n1 == nullptr and n2 == nullptr) {
        return true;
      }
      else if ((n1 == nullptr and n2 != nullptr) or (n1 != nullptr and n2 == nullptr)) {
        return false;
      }
      if (is_leaf(n1) and is_leaf(n2)) {
        return n1->val == n2->val;
      }
      else if ((is_leaf(n1) and not is_leaf(n2)) or (not is_leaf(n1) and is_leaf(n2))) {
        return false;
      }
      else if (not is_leaf(n1) and not is_leaf(n2)) {
        if (n1->val != n2->val) {
          return false;
        }
        else if (n1->left != nullptr and n2->right != nullptr and n1->right == nullptr and n2->left == nullptr) {
          return n1->left->val == n2->right->val and f(n1->left, n2->right);
        }
        else if (n1->left == nullptr and n2->right == nullptr and n1->right != nullptr and n2->left != nullptr) {
          return n1->right->val == n2->left->val and f(n1->right, n2->left);
        }
        else if (n1->left != nullptr and n2->left != nullptr and n1->right == nullptr and n2->right == nullptr) {
          return n1->left->val == n2->left->val and f(n1->left, n2->left);
        }
        else if (n1->left == nullptr and n2->left == nullptr and n1->right != nullptr and n2->right != nullptr) {
          return n1->right->val == n2->right->val and f(n1->right, n2->right);
        }
        else if (n1->left != nullptr and n1->right != nullptr and n2->left != nullptr and n2->right != nullptr) {
          return (n1->left->val == n2->left->val and n1->right->val == n2->right->val and f(n1->left, n2->left) and f(n1->right, n2->right))
              or (n1->left->val == n2->right->val and n1->right->val == n2->left->val and f(n1->left, n2->right) and f(n1->right, n2->left));
        }
        else {
          return false;
        }
      }
      else throw std::domain_error("");
    };

    return f(root1, root2);
  }
};
