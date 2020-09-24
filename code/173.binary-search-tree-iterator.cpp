class BSTIterator {
 private:
  std::deque<TreeNode*> DQ;

  void refill_left(TreeNode* node) {
    if (node != nullptr) {
      DQ.emplace_front(node);
      refill_left(node->left);
    }
  };
  
 public:
  BSTIterator(TreeNode* root) : DQ{} {
    refill_left(root);
  }

  /** @return the next smallest number */
  int next() {
    const auto result = DQ.front();
    DQ.pop_front();
    if (result->right != nullptr) {
      refill_left(result->right);
    }
    return result->val;
  }
    
  /** @return whether we have a next smallest number */
  bool hasNext() {
    return not std::empty(DQ);
  }
};

