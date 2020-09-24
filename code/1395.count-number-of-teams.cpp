template <class T>
struct plus_monoid {
  using value_type = T;
  value_type unit() const { return value_type(); }
  value_type mult(value_type a, value_type b) const { return a + b; }
};

template <typename Monoid>
struct binary_index_tree {
  using value_type = typename Monoid::value_type;
  
  std::vector<value_type> data;
  static constexpr Monoid mon = {};

  binary_index_tree(std::size_t n) {
    data.resize(n, mon.unit());
  }

  void point_append(std::size_t i, value_type val) { // data[i] += z
    for (std::size_t j = i + 1; j <= std::size(data); j += (j & -j)) {
      data[j - 1] = mon.mult(data[j - 1], val);
    }
  }

  value_type initial_range_concat(std::size_t i) {   // [0, i)
    value_type acc = mon.unit();
    for (std::size_t j = i; j >= 1; j -= (j & -j)) {
      acc = mon.mult(data[j - 1], acc);
    }
    return acc;
  }
};


template <typename TCoord>
struct coordinate_map {
  std::unordered_map<TCoord, int> f;
  std::vector<TCoord> f_inv;

  coordinate_map(const std::vector<TCoord>& data) {
    std::copy(std::begin(data), std::end(data), std::back_inserter(f_inv));
    std::sort(std::begin(f_inv), std::end(f_inv));
    f_inv.erase(std::unique(std::begin(f_inv), std::end(f_inv)), std::end(f_inv));
    std::transform(std::begin(f_inv), std::end(f_inv), std::inserter(f, std::begin(f)), [&, rank = 0](auto &&x) mutable {
      return std::pair{x, rank++};
    });
  }

  int operator()(TCoord c) const { return f.at(c); }

  TCoord operator[](int rank) const { return f_inv[rank]; }

  std::size_t size() const {
    return std::size(f_inv);
  }
};


class Solution {
 public:
  int numTeams(vector<int>& rating) {
    const auto cdmap = coordinate_map<int>(rating);

    const auto n = cdmap.size();

    const auto [i_less, i_more] = [&, BIT = binary_index_tree<plus_monoid<int>>(n)]() mutable {
      auto self_iless = std::vector<int>(n, 0);
      auto self_imore = std::vector<int>(n, 0);
      for (int i = 0; i < std::size(rating); ++i) {
        self_iless[i] = BIT.initial_range_concat(cdmap(rating[i]));
        self_imore[i] = BIT.initial_range_concat(n) - BIT.initial_range_concat(cdmap(rating[i]));
        BIT.point_append(cdmap(rating[i]), 1);
      }
      return std::make_pair(self_iless, self_imore);
    }();

    const auto [k_less, k_more] = [&, BIT = binary_index_tree<plus_monoid<int>>(n)]() mutable {
      auto self_kless = std::vector<int>(n, 0);
      auto self_kmore = std::vector<int>(n, 0);
      for (int i = std::size(rating) - 1; i >= 0; --i) {
        self_kless[i] = BIT.initial_range_concat(cdmap(rating[i]));
        self_kmore[i] = BIT.initial_range_concat(n) - BIT.initial_range_concat(cdmap(rating[i]));
        BIT.point_append(cdmap(rating[i]), 1);
      }
      return std::make_pair(self_kless, self_kmore);
    }();

    const auto solution = [&, i_less = i_less, i_more = i_more, k_less = k_less, k_more = k_more](int acc = 0) {
      for (int i = 0; i < std::size(rating); ++i) {
        acc += i_less[i] * k_more[i] + i_more[i] * k_less[i];
      }
      return acc;
    }();

    return solution;
    
  }
};
