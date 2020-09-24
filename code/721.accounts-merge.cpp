struct union_find_tree {
  mutable std::vector<int> data;
  union_find_tree() = default;
  explicit union_find_tree(std::size_t n) : data(n, -1) {};

  bool is_root(int i) {
    return data[i] < 0;
  }

  int find_root(int i) {
    return is_root(i) ? i : data[i] = find_root(data[i]);
  };

  int tree_size (int i) {
    return -data[find_root(i)];
  }

  bool merge(int i, int j) {
    auto root_i = find_root(i);
    auto root_j = find_root(j);
    if (root_i == root_j) {
      return false;
    }
    else {
      if (tree_size(root_i) < tree_size(root_j)) {
        std::swap(root_i, root_j);
      }
      std::exchange(data[root_i], data[root_i] + data[root_j]);
      std::exchange(data[root_j], root_i);
      return true;
    }
  }

  bool is_same(int i, int j) {
    return find_root(i) == find_root(j);
  }
};

class Solution {
 public:
  vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    const auto ID = [&](std::unordered_map<std::string, int> self = {}) {
      auto id = 0;
      for (const auto& account : accounts) {
        for (int i = 1; i < std::size(account); ++i) {
          if (not self.count(account[i])) {
            self[account[i]] = id++;
          }
        }
      }
      return self;
    }();

    const auto RID = [&](std::unordered_map<int, std::string> self = {}) {
      for (const auto & [account, id] : ID) {
        self[id] = account;
      }
      return self;
    }();

    const int n = std::size(ID);

    struct state_t {
      mutable union_find_tree DSU;
    };

    const auto ST = [&](state_t self = {}) {
      self.DSU = union_find_tree(n);
      for (const auto& account : accounts) {
        for (int i = 1; i < std::size(account); ++i) {
          self.DSU.merge(ID.at(account[i]), ID.at(account[1]));
        }
      }
      return self;
    }();

    const auto CC = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      for (int i = 0; i < n; ++i) {
        self[ST.DSU.find_root(i)].emplace_back(i);
      }
      return self;
    }();


    const auto CC_label = [&](std::unordered_map<int, std::string> self = {}) {
      for (const auto & account : accounts) {
        const auto name = account[0];
        const auto one_of_account = account[1];
        self[ST.DSU.find_root(ID.at(one_of_account))] = name;
      }
      return self;
    }();

    const auto solution = [&](std::vector<std::vector<std::string>> self = {}) {
      for (auto & [id, cc] : CC) {
        const auto sorted_component = [&, &id = id, &cc = cc](std::vector<std::string> x = {}) {
          x.emplace_back(CC_label.at(id));
          std::transform(std::begin(cc), std::end(cc), std::back_inserter(x), [&](auto &x) {
            return RID.at(x);
          });
          std::sort(std::begin(x) + 1, std::end(x));
          return x;
        }();
        self.emplace_back(sorted_component);
      };
      return self;
    }();
    
    return solution;
  }
};
