class Solution {
 public:
  Node* copyRandomList(Node* head) {
    std::function<Node*(Node*)> clone = [&, memo = std::unordered_map<Node*, Node*>{}](Node* n) mutable {
      if (n == nullptr) {
        return static_cast<Node*>(nullptr);
      }
      else if (memo.find(n) != std::end(memo)) {
        return memo.at(n);
      }
      else {
        Node* clone_n = new Node(n->val);
        memo[n] = clone_n;
        clone_n->next = clone(n->next);
        clone_n->random = clone(n->random);
        return clone_n;
      }
    };

    return clone(head);
  }
};
