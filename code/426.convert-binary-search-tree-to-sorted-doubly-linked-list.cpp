class Solution {
public:
    Node* treeToDoublyList(Node* root) {
      auto concat = [&](Node* lhead, Node* n, Node* rhead) -> Node* {
          auto new_head = std::optional<Node*>{};
          auto new_tail = std::optional<Node*>{};
          if (lhead != nullptr) {
            auto ltail = lhead->left;
            new_head.emplace(lhead);
            ltail->right = n;
            n->left = ltail;
          }
          if (rhead != nullptr) {
            auto rtail = rhead->left;
            new_tail.emplace(rtail);
            rhead->left = n;
            n->right = rhead;
          }
          std::exchange(new_head.value_or(n)->left, new_tail.value_or(n));
          std::exchange(new_tail.value_or(n)->right, new_head.value_or(n));
          return new_head.value_or(n);
      };
      
      std::function<Node*(Node*)> fold = [&](Node* n) {
        if (n == nullptr) {
          return (Node*) nullptr;
        }
        else {
          return concat(fold(n->left), n, fold(n->right));
        }
      };

      return fold(root);
    }
};
