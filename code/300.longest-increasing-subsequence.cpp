class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    struct {
      mutable std::vector<int> piles;
    } ST;

    const int n = std::size(nums);
    
    // patience sorting algorithm
    std::function<void(int)> fold = [&](int i) {
      if (i == n) {
        return;
      }
      else {
        const auto llmost_pile_top = std::lower_bound(std::begin(ST.piles), std::end(ST.piles), nums[i]);
        if (llmost_pile_top == std::end(ST.piles)) {
          ST.piles.emplace_back(nums[i]);
        }
        else {
          std::exchange(*llmost_pile_top, nums[i]);
        }
        return fold(i + 1);
      }
    };

    return (fold(0), std::size(ST.piles));
  }
};
