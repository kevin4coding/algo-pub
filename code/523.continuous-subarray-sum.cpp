class Solution {
 public:
  bool checkSubarraySum(vector<int>& nums, int k) {
    const int n = std::size(nums);
    
    struct {
      mutable std::unordered_map<int, int> R = {};
      mutable int acc_sum = 0;
      mutable bool valid = false;
    } ST;

    std::function<void(int)> fold = [&](int i) {
      if (i == n or ST.valid == true) {
        return;
      }
      else {
        ST.acc_sum = k == 0 ? ST.acc_sum + nums[i] : (ST.acc_sum + nums[i]) % k;
        if (k == 0 and ST.acc_sum == 0 and i >= 1)  {
          return std::void_t<>(ST.valid = true);
        }
        else if (k != 0 and ST.acc_sum % k == 0 and i >= 1) {
          return std::void_t<>(ST.valid = true);
        }
        else if (ST.R.count(ST.acc_sum) and i - ST.R[ST.acc_sum] >= 2) {
          return std::void_t<>(ST.valid = true);
        }
        else if (ST.R.count(ST.acc_sum) and i - ST.R[ST.acc_sum] < 2) {
          return fold(i + 1);
        }
        else {
          ST.R[ST.acc_sum] = i;
          return fold(i + 1);
        }
      }
    };

    return fold(0), ST.valid;
  }
};
