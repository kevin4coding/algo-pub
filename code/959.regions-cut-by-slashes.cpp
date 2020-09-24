struct union_find_tree {
  mutable std::vector<int> data;
  mutable int cc_count;

  union_find_tree() = default;
  explicit union_find_tree(std::size_t n) : data(n, -1), cc_count(n) {}
    
  
  int find_root(int i) {
    return data[i] < 0 ? i : data[i] = find_root(data[i]);
  }

  int tree_size(int i) {
    return -data[find_root(i)];
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
  int regionsBySlashes(vector<string>& grid) {
    const int R = std::size(grid);
    const int C = std::size(grid[0]);
    const int N = R * C;
    
    const auto solution = [&]() {
      auto DSU = union_find_tree(4 * R * C);
      
      for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
          const auto up = 4 * (r * C + c);
          const auto right = up + 1;
          const auto down = up + 2;
          const auto left = up + 3;
          if (grid[r][c] == '/') {
            DSU.merge(up, left);
            DSU.merge(right, down);
          }
          else if (grid[r][c] == '\\') {
            DSU.merge(up, right);
            DSU.merge(left, down);
          }
          else if (grid[r][c] == ' ') {
            DSU.merge(up, right);
            DSU.merge(right, down);
            DSU.merge(down, left);
          }
          if (r < R - 1) {
            // down neighbor
            DSU.merge(down, up + 4 * C + 0);
          }
          if (c < C - 1) {
            // right neighbor
            DSU.merge(right, up + 4 + 3);
          }
        }
      }

      return DSU.cc_count;
    }();

    return solution;
  }
};
