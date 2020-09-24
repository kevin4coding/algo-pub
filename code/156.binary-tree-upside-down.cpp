class Solution {
 public:
  TreeNode *upsideDownBinaryTree(TreeNode *root) {
    std::function<TreeNode*(TreeNode*, TreeNode*, TreeNode*)> fmap = [&](TreeNode* node, TreeNode* parent, TreeNode* parent_rch) {
      if (node == nullptr) 
        return parent;
      else 
        return fmap(std::exchange(node->left, parent_rch), node, std::exchange(node->right, parent));
    };
    return fmap(root, nullptr, nullptr);
  }
};
