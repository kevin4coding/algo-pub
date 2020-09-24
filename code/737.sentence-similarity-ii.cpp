struct union_find_tree {
  mutable std::vector<int> data;

  union_find_tree() = default;
  explicit union_find_tree(std::size_t n) : data(n, -1) {}

  bool is_root(int i) {
    return data[i] < 0;
  }

  void resize(std::size_t n) {
    data.resize(n, -1);
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
};

class Solution {
 public:
  bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
    struct state_t {
      mutable union_find_tree DSU;
    };

    const auto ID = [&](std::unordered_map<std::string, int> self = {}) {
      auto id = 0;
      for (const auto & x : words1) {
        if (not self.count(x)) {
          self[x] = id++;
        }
      }
      for (const auto & x : words2) {
        if (not self.count(x)) {
          self[x] = id++;
        }
      }
      for (const auto & group : pairs) {
        for (const auto & x : group) {
          if (not self.count(x)) {
            self[x] = id++;
          }
        }
      }
      return self;
    }();

    const auto ST = [&](state_t self = {}) {
      self.DSU.resize(std::size(ID));
      for (const auto & group : pairs) {
        for (int i = 0; i < std::size(group); ++i) {
          self.DSU.merge(ID.at(group[i]), ID.at(group[0]));
        }
      }
      return self;
    }();

    const auto cc1 = [&](std::vector<int> self = {}) {
      std::transform(std::begin(words1), std::end(words1), std::back_inserter(self), [&](auto &&x) {
        return ST.DSU.find_root(ID.at(x));
      });
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    const auto cc2 = [&](std::vector<int> self = {}) {
      std::transform(std::begin(words2), std::end(words2), std::back_inserter(self), [&](auto &&x) {
        return ST.DSU.find_root(ID.at(x));
      });
      std::sort(std::begin(self), std::end(self));
      return self;
    }();

    return cc1 == cc2;
  }
};
