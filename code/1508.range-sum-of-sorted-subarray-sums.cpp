class Solution {
public:
  int rangeSum(vector<int>& nums, int n, int left, int right) {
    using int64 = long long;
    const int64 mod = 1e9 + 7;
    
    auto make_prefix = [&](const std::vector<int>& arr) {
      auto result = std::vector<int>(std::size(arr), 0);
      for (int i = 0; i < std::size(arr); ++i) {
        if (i == 0)
          result[i] = arr[i];
        else
          result[i] = result[i - 1] + arr[i];
      }
      return result;
    };

    auto C = [&](int target) {
      auto acc = int{0};
      for (auto [i, j, subacc_sum] = std::tuple{0, 0, 0}; i < n; ++i) {
        subacc_sum += nums[i];
        while (i - j + 1 > 0 and subacc_sum > target) {
          subacc_sum -= nums[j++];
        }
        if (i - j + 1 > 0) {
          acc += i - j + 1;
        }
      }
      return acc;
    };

    auto bsearch = [&](int rank) {
      std::optional<int> result = {};
      std::function<void(int, int)> go = [&](int lo, int hi) {
        const int mid = lo + (hi - lo) / 2;
        if (lo > hi) {
          return;
        }
        else if (C(mid) < rank) {
          go(mid + 1, hi);
        }
        else if (C(mid) >= rank) {
          result.emplace(mid);
          go(lo, mid - 1);
        }
      };
      return go(1, std::accumulate(std::begin(nums), std::end(nums), 0)), result;
    };

    auto G = [&, P = make_prefix(nums), SP = make_prefix(make_prefix(nums))](int target) {
      auto acc = int64{0};
      for (auto [i, j, subacc_sum] = std::tuple{0, 0, int64{0}}; i < n; ++i) {
        subacc_sum += nums[i];
        while (i - j + 1 > 0 and subacc_sum > target) {
          subacc_sum -= nums[j++];
        }
        if (i - j + 1 == 0) {
          continue;
        }
        else if (j == 0) {
          acc += (i + 1) * P[i] - (i >= 1 ? SP[i - 1] : 0);
        }
        else if (j >= 1) {
          acc += (i - j + 1) * P[i] - (SP[i - 1] - (j == 1 ? 0 : SP[j - 2]));
        }
      }
      return acc;
    };
    
    auto F = [&](int rank) {
      const auto lower = bsearch(rank).value();
      return G(lower - 1) + (rank - C(lower - 1)) * lower;
    };

    return (F(right) - F(left - 1)) % mod;
  }
};

