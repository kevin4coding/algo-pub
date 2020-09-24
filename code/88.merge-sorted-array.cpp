class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    std::function<void(int, int, int)> f = [&](int i, int n1, int n2) {
      if (i < 0) {
        return;
      }
      else if (n1 < 0) {
        nums1[i] = nums2[n2];
        f(i - 1, n1, n2 - 1);
      }
      else if (n2 < 0) {
        nums1[i] = nums1[n1];
        f(i - 1, n1 - 1, n2);
      }
      else if (nums1[n1] <= nums2[n2]) {
        nums1[i] = nums2[n2];
        f(i - 1, n1, n2 - 1);
      }
      else if (nums1[n1] > nums2[n2]) {
        nums1[i] = nums1[n1];
        f(i - 1, n1 - 1, n2);
      }
      else throw std::domain_error("");
    };
    go(n + m - 1, m - 1, n - 1);
  }
};
