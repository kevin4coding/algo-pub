struct union_find_tree {
  std::vector<int> data;
  union_find_tree() = default;

  explicit union_find_tree(int n) : data(n, -1) {}
  
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
      return true;
    }
  }
};


class Solution {
 public:
  string smallestEquivalentString(string A, string B, string S) {
    const int n = std::size(A);

    // mutable state
    auto DSU = union_find_tree(26);
    
    const auto CC = [&](std::unordered_map<char, std::vector<char>> self = {}) {

      for (int i = 0; i < n; ++i) {
        DSU.merge(A[i] - 'a', B[i] - 'a');
      }

      for (int i = 0; i < n; ++i) {
        const auto [a, b] = std::pair{A[i], B[i]};
        self[DSU.find_root(a - 'a') + 'a'].emplace_back(a);
        self[DSU.find_root(b - 'a') + 'a'].emplace_back(b);
      }

      for (auto & [_, cc] : self) {
        std::sort(std::begin(cc), std::end(cc));
      }
      return self;
    }();

    const auto solution = [&](std::string acc = {}) {
      for (const auto x : S) {
        // his create unnecessary side effects. but ok for this problem.
        // A better way to handle it is to use a hashmap to track the root for all element in A and B.
        if (not CC.count(DSU.find_root(x - 'a') + 'a')) {
          acc.push_back(x);
        }
        else {
          acc.push_back(CC.at(DSU.find_root(x - 'a') + 'a')[0]);
        }
      }
      return acc;
    }();


    return solution;
    
  }
};
