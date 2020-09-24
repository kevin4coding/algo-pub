struct union_find_tree {
  std::vector<int> data;
  bool flag_rank_heuristic;
  union_find_tree() = default;
  explicit union_find_tree(std::size_t n, bool flag_rank_heuristic = true) : data(n, -1),
                                                                             flag_rank_heuristic(flag_rank_heuristic) {}
  bool is_root(int i) { return data[i] < 0; }
  int find_root(int i) { return is_root(i) ? i : (data[i] = find_root(data[i])); }
  int tree_size(int i) { return - data[find_root(i)]; }
  int unite_trees(int i, int j) {
    i = find_root(i); j = find_root(j);
    if (i != j) {
      if (flag_rank_heuristic and tree_size(i) < tree_size(j)) std::swap(i, j);
      data[i] += data[j];
      data[j] = i;
    }
    return i;
  }
  bool is_same(int i, int j) { return find_root(i) == find_root(j); }
};

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    struct tree_record_t {
      int size;
      std::unordered_map<TreeNode*, int> id;
    };

    const auto tree_info = tree_record_t {
      // init size
      .size = [&] {
        std::function<int(TreeNode*)> fold = [&](TreeNode* node) {
          if (node == nullptr) {
            return 0;
          }
          else {
            return 1 + fold(node->left) + fold(node->right);
          }
        };
        return fold(root);
      }(),
      // init id
      .id = [&](std::unordered_map<TreeNode*, int> self = {}) {
        std::function<void(TreeNode*)> fold = [&, counter = 0](TreeNode* node) mutable {
          if (node == nullptr) {
            return;
          }
          else {
            self[node] = counter++;
            fold(node->left);
            fold(node->right);
          }
        };
        return fold(root), self;
      }()
    };

    auto LCA = [&](TreeNode* node) {
      std::optional<int> result = {};
      std::function<void(TreeNode*)> fold = [&,
                                             DSU = union_find_tree(tree_info.size, false),
                                             visit = std::vector<bool>(tree_info.size, false)](TreeNode* u) mutable {
        
        if (u == nullptr or result.has_value()) {
          return;
        }
        else {
          if (u->left) {
            fold(u->left);
            DSU.unite_trees(tree_info.id.at(u), tree_info.id.at(u->left));
          }
          if (u->right) {
            fold(u->right);
            DSU.unite_trees(tree_info.id.at(u), tree_info.id.at(u->right));
          }
        }
        visit[tree_info.id.at(u)] = true;
        if (u == p and visit[tree_info.id.at(q)]) {
          result.emplace(DSU.find_root(tree_info.id.at(q)));
        }
        else if (u == q and visit[tree_info.id.at(p)]) {
          result.emplace(DSU.find_root(tree_info.id.at(p)));
        }
      };
      return fold(node), [&]() {
        for (const auto [node, id] : tree_info.id) {
          if (id == result.value()) {
            return node;
          }
        }
        throw std::domain_error("non match found");
      }();
    };

    return LCA(root);
  }
};
