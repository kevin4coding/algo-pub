class Solution {
 public:
  bool PredictTheWinner(vector<int>& nums) {
    struct {
      mutable std::optional<int> f[100][100] = {};
    } mempool;

    const int n = std::size(nums);

    std::function<int(int, int)> f = [&, memo = mempool.f](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i == j) {
            return nums[i];
          }
          else if (i + 1 == j) {
            return std::max(nums[i], nums[j]) - std::min(nums[i], nums[j]);
          }
          else {
            return std::max(nums[i] - f(i + 1, j), nums[j] - f(i, j - 1));
          }
        }());
      }
    };

    return f(0, n - 1) >= 0;
  }
};


