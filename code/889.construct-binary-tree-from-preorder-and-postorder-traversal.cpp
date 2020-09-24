class Solution {
 public:
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    const int N = std::size(pre);
      
    const auto post_val_id_map = [&](std::unordered_map<int ,int> self = {}) {
      for (int i = 0; i < N; ++i) {
        self[post[i]] = i;
      }
      return self;
    }();

    std::function<TreeNode*(int, int, int, int)> build = [&](int lpre, int rpre, int lpo, int rpo) {
      if (lpre > rpre) {
        return static_cast<TreeNode*>(nullptr);
      }
      else if (lpre == rpre) {
        return new TreeNode(pre[lpre]);
      }
      else {
        const auto [id, L] = std::pair{post_val_id_map.at(pre[lpre + 1]), post_val_id_map.at(pre[lpre + 1]) - lpo + 1};
        return new TreeNode(pre[lpre],
                            build(lpre + 1, lpre + 1 + L - 1, lpo, id),
                            build(lpre + L + 1, rpre, id + 1, rpo - 1));
      }
    };

    return build(0, N - 1, 0, N - 1);
  }
};
