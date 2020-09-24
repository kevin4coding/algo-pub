class Solution {
 public:
  int removeElement(vector<int>& nums, int val) {
    const int n = std::size(nums);
    
    std::function<int(int, int)> go = [&](int i, int j) {
      if (j == n) {
        return i;
      }
      else if (nums[j] == val) {
        return go(i, j + 1);
      }
      else if (nums[j] != val) {
        nums[i] = nums[j];
        return go(i + 1, j + 1);
      }
      throw std::domain_error("");
    };

    return go(0, 0);
  }
};
 
