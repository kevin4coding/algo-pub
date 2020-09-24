class Solution {
 public:
  Node* cloneTree(Node* root) {
    if (root == nullptr) {
      return nullptr;
    }
    else if (std::size(root->children) == 0) {
      return new Node(root->val);
    }
    else {
      return new Node(root->val, [&](std::vector<Node*> self = {}) {
          std::transform(std::begin(root->children), std::end(root->children), std::back_inserter(self), [&](Node* x) {
            return cloneTree(x);
          });
          return self;
        }());
    }
  }
};
