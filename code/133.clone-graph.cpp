class Solution {
 public:
  Node* cloneGraph(Node* node) {
    std::function<Node*(Node*)> build = [&, memo = std::unordered_map<Node*, Node*>{}](Node* n) mutable {
      if (n == nullptr) {
        return static_cast<Node*>(nullptr);
      }
      else if (memo.count(n)) {
        return memo[n];
      }
      else {
        memo[n] = new Node(n->val);
        for (const auto neighbor : n->neighbors) {
          memo[n]->neighbors.emplace_back(build(neighbor));
        }
        return memo[n];
      }
    };
    return build(node);
  }
};
