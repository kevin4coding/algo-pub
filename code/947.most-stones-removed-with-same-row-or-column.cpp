struct union_find_tree {
  union_find_tree() = default;
  explicit union_find_tree(int n) : data(n, -1), cc_count(n) {}

  void resize(int n) {
    data.resize(n, -1);
    cc_count = n;
  }
  
  bool is_root(int i) {
    return data[i] < 0;
  }

  int tree_size(int i) {
    return -data[find_root(i)];
  }

  int find_root(int i) {
    return is_root(i) ? i : data[i] = find_root(data[i]);
  }
  
  
  bool merge(int i, int j) {
    i = find_root(i);
    j = find_root(j);
    if (i == j) {
      return false;
    }
    else {
      if (tree_size(i) < tree_size(j)) {
        std::swap(i, j);
      }
      std::exchange(data[i], data[i] + data[j]);
      std::exchange(data[j], i);
      --cc_count;
      return true;
    }
  }
      
};

class Solution {
 public:
  int removeStones(vector<vector<int>>& stones) {
    const auto n = std::size(stones);

    auto connected = [&](const std::vector<int>& s1, const std::vector<int>& s2) {
      return s1[0] == s2[0] or s1[1] == s2[1];
    };
    
    const auto solution = [&]() {
      auto DSU = union_find_tree(n);
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          if (connected(stones[i], stones[j])) {
            DSU.merge(i, j);
          }
        }
      }

      return n - DSU.cc_count;
    }();

    return solution;
    
  }
};
