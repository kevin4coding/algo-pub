class Solution {
 public:
  vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    const int n = std::size(nums);
    const int bucket_size = 105;
    
    const auto bucket = [&](std::vector<int> self ={}) {
      self.resize(bucket_size, 0);
      for (int i = 0; i < n; ++i) {
        ++self[nums[i]];
      }
      return self;
    }();

    const auto prefix_sum = [&](std::vector<int> self = {}) {
      self.resize(bucket_size, 0);
      for (int i = 0; i < bucket_size; ++i) {
        if (i == 0) {
          self[i] = bucket[i];
        }
        else {
          self[i] = self[i - 1] + bucket[i];
        }
      }
      return self;
    }();


    auto RSQ = [&](int i, int j) {
      if (i == 0) {
        return prefix_sum[j];
      }
      else {
        return prefix_sum[j] - prefix_sum[i - 1];
      }
    };

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(n, 0);
      for (int i = 0; i < n; ++i) {
        if (nums[i] == 0) {
          self[i] = 0;
        }
        else { 
          self[i] = RSQ(0, nums[i] - 1);
        }
      }
      return self;      
    }();

    return solution;
  }
};
