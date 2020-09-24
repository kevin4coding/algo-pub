class Solution {
 public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    const int n1 = std::size(nums1);
    const int n2 = std::size(nums2);

    auto k_subseq = [](const std::vector<int>& arr, int k) {
      const int n = std::size(arr);
      auto DQ = std::vector<int>{};
      
      for (int i = 0; i < n; ++i) {
        while (not std::empty(DQ) and (n - 1 - i + 1) + std::size(DQ) - 1 >= k and arr[i] > DQ.back()) {
          DQ.pop_back();
        }
        if (std::size(DQ) < k) {
          DQ.emplace_back(arr[i]);
        }
      };
      return DQ;
    };


    auto merge = [](const std::vector<int>& arr1, const std::vector<int>& arr2) {
      auto acc = std::vector<int>{};
      const int n1 = std::size(arr1);
      const int n2 = std::size(arr2);
      
      std::function<void(int, int)> fold = [&](int i, int j) {
        if (i == n1 and j == n2) {
          return;
        }
        else if (not std::lexicographical_compare(std::begin(arr1) + i, std::end(arr1),
                                                  std::begin(arr2) + j, std::end(arr2))) {
          acc.emplace_back(arr1[i]);
          return fold(i + 1, j);
        }
        else {
          acc.emplace_back(arr2[j]);
          return fold(i, j + 1);
        }
      };

      return fold(0, 0), acc;
    };

    
    auto solve = [&](std::vector<int> acc = {}) {
      for (int i = 0; i <= n1 ; ++i) {
        if (k - i <= n2 and k - i >= 0) {
          acc = std::max(acc, merge(k_subseq(nums1, i), k_subseq(nums2, k - i)));
        }
      }
      return acc;
    };

    return solve();
  }
};
