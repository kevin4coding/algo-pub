template <typename T>
struct plus_monoid {
  using value_type = T;
  value_type unit() const { return value_type{}; }
  value_type mult(value_type a, value_type b) const { return a + b; }
};



template <typename Monoid>
struct binary_index_tree {
  using value_type = typename Monoid::value_type;
  
  std::vector<value_type> data;
  static constexpr Monoid mon = {};

  binary_index_tree(std::size_t n) { data.resize(n, mon.unit()); }

  static constexpr int lowbit(int i) { return i & (-i); }

  void point_append(std::size_t i, value_type val) { // data[i] += z
    for (std::size_t j = i + 1; j <= std::size(data); j += lowbit(j)) 
      data[j - 1] = mon.mult(data[j - 1], val);
  }

  value_type initial_range_concat(std::size_t i) {   // [0, i)
    value_type acc = mon.unit();
    for (std::size_t j = i; j >= 1; j -= lowbit(j)) 
      acc = mon.mult(data[j - 1], acc);
    return acc;
  }
};


class Solution {
 public:
  vector<int> processQueries(vector<int>& queries, int m) {
    const int q = std::size(queries);

    auto make_init_position = [&](std::vector<int> self = {}) {
      self.resize(m + 1);
      for (int i = 1; i <= m; ++i) {
        self[i] = q + i;
      }
      return self;
    };
    
    auto make_init_BIT = [&]() {
      auto self = binary_index_tree<plus_monoid<int>>(q + m + 1);
      for (int i = 1; i <= m; ++i) {
        self.point_append(i + q, 1);
      }
      return self;
    };

    const auto solution = [&,
                           position = make_init_position(),
                           BIT = make_init_BIT()](std::vector<int> self = {}) mutable {
      for (int i = 0; i < q; ++i) {
        BIT.point_append(position[queries[i]], -1);
        self.emplace_back(BIT.initial_range_concat(position[queries[i]]));
        BIT.point_append(position[queries[i]] = q - i, 1);
      }
      return self;
    }();

    return solution;
        
  }
};
