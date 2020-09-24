class Solution {
 public:
  int countPairs(TreeNode* root, int distance) {
    const auto parent = [&](std::unordered_map<TreeNode*, TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n == root) {
            self[n] = nullptr;
          }
          if (n->left != nullptr) {
            self[n->left] = n;
          }
          if (n->right != nullptr) {
            self[n->right] = n;
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    auto count_from = [&](TreeNode* start) {
      auto acc = 0;
      std::function<void(TreeNode*, int)> fold = [&, visited = std::unordered_map<TreeNode*, bool>{}](TreeNode* n, int d) mutable {
        if (n == nullptr or d > distance) {
          return;
        }
        else {
          visited[n] = true;
          if (n->left == nullptr and n->right == nullptr and n != start and d <= distance) {
            ++acc;
          }
          for (const auto next : std::array{parent.at(n), n->left, n->right}) {
            if (next != nullptr and not visited[next]) {
              fold(next, d + 1);
            }
          }
        }
      };
      return fold(start, 0), acc;
    };

    const auto solution = [&](int acc = 0) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->left == nullptr and n->right == nullptr) {
            acc += count_from(n);
          }
          fold(n->left);
          fold(n->right);
        }
      };

      return fold(root), acc / 2;
    }();

    return solution;
  }
};
