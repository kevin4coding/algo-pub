struct union_find_tree {
  mutable std::vector<int> data;

  union_find_tree(std::size_t n) : data(n, -1) {}

  bool is_root(int i) {
    return data[i] < 0;
  }
  
  int find_root(int i) {
    return is_root(i) ? i : data[i] = find_root(data[i]);
  }
  
  int tree_size(int i) {
    return -data[find_root(i)];
  }

  bool merge(int i, int j) {
    auto [root_i, root_j] = std::pair{find_root(i), find_root(j)};
    if (root_i == root_j) {
      return true;
    }
    else {
      if (tree_size(root_i) < tree_size(root_j)) {
        std::swap(root_i, root_j);
      }
      std::exchange(data[root_i], data[root_i] + data[root_j]);
      std::exchange(data[root_i], root_j);
      return false;
    }
  }

  bool is_same(int i, int j) {
    return find_root(i) == find_root(j);
  }
};


class Solution {
 public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    const auto solution = [&, DSU = union_find_tree(1005)](std::vector<int> self = {}) mutable {
      for (const auto & e : edges) {
        const auto [u, v] = std::pair{e[0], e[1]};
        if (DSU.is_same(u, v)) {
          std::exchange(self, {u, v});
        }
        else {
          DSU.merge(u, v);
        }
      }
      return self;
    }();

    return solution;
    
  }
};
