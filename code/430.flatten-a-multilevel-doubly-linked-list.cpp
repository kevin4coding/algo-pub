class Solution {
 public:
  Node* flatten(Node* head) {
    std::function<void(Node*)> fold = [&, pre = (Node*)nullptr](Node* n) mutable {
      if (n == nullptr) {
        return;
      }
      else {
        std::exchange(pre, n);
        if (n->child != nullptr) {
          fold(n->child);
          if (n->next) {
            pre->next = n->next;
            n->next->prev = pre;
          }
          n->child->prev = n;
          n->next = n->child;
          n->child = nullptr;
        }
        fold(pre->next);
      }
    };
    
    return fold(head), head;
  }
};
