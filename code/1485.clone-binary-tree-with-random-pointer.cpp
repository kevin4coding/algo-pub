class Solution {
 public:
  NodeCopy* copyRandomBinaryTree(Node* root) {
    const auto node_to_id = [&](std::unordered_map<Node*, int> self = {}) {
      std::function<void(Node*)> fold = [&, id = 0](Node* n) mutable {
        if (n == nullptr) {
          return;
        }
        else {
          self[n] = id++;
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    std::function<NodeCopy*(Node*)> clone_without_random = [&](Node* n) {
      if (n == nullptr) {
        return static_cast<NodeCopy*>(nullptr);
      }
      else {
        return new NodeCopy(n->val,
                            clone_without_random(n->left),
                            clone_without_random(n->right),
                            nullptr);
      }
    };

    const auto solution = [&](NodeCopy* self = nullptr) {
      std::exchange(self, clone_without_random(root));
      
      const auto id_to_node = [&](std::unordered_map<int, NodeCopy*> x = {}) {
        std::function<void(NodeCopy*)> fold = [&, id = 0](NodeCopy* n) mutable {
          if (n == nullptr) {
            return;
          }
          else {
            x[id++] = n;
            fold(n->left);
            fold(n->right);
          }
        };
        return fold(self), x;
      }();

      std::function<void(NodeCopy*, Node*)> fold = [&](NodeCopy* n, Node* m) {
        if (n == nullptr) {
          return;
        }
        else {
          if (m->random != nullptr) {
            n->random = id_to_node.at(node_to_id.at(m->random));
          }
          fold(n->left, m->left);
          fold(n->right, m->right);
        }
      };
      return fold(self, root), self;
    }();

    return solution;
  }
};
