class CBTInserter {
 private:
  mutable std::vector<TreeNode*> tree;
  
 public:
  CBTInserter(TreeNode* root) {
    auto Q = std::deque<TreeNode*>{root};
    std::function<void(void)> bfs = [&]() {
      if (std::empty(Q)) {
        return;
      }
      else {
        const auto n = Q.front();
        Q.pop_front();
        tree.emplace_back(n);
        if (n->left != nullptr) {
          Q.emplace_back(n->left);
        }
        if (n->right != nullptr) {
          Q.emplace_back(n->right);
        }
      }
      bfs();
    };
    bfs();
  }
    
  int insert(int v) {
    const auto ch = tree.emplace_back(new TreeNode(v));
    const auto id = std::size(tree) - 1;
    const auto parent = tree[(id - 1) / 2];
    if (id % 2 == 1) {
      std::exchange(parent->left, tree.back());
    }
    else if (id % 2 == 0) {
      std::exchange(parent->right, tree.back());
    }
    return parent->val;
  }
    
  TreeNode* get_root() {
    return tree[0];
  }
};
