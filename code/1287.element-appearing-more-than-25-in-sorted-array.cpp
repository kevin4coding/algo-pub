class Solution {
 public:
  int findSpecialInteger(vector<int>& arr) {
    const int n = std::size(arr);
    
    std::function<int(int, int)> go = [&](int ll, int rr) {
      if (rr - ll + 1 > 0.25 * n) {
        return arr[rr];
      }
      else if (rr + 1 < n and arr[rr + 1] == arr[ll]) {
        return go(ll, rr + 1);
      }
      else if (rr + 1 < n and arr[rr + 1] != arr[ll]) {
        return go(rr + 1, rr + 1);
      }
      else if (rr == n - 1 and arr[rr] == arr[ll] and rr - ll + 1 > 0.25 * n) {
        return arr[rr];
      }
      else if (rr == n - 1 and arr[rr] != arr[ll] and 0.25 * n <= 1) {
        return arr[rr];
      }
      else throw std::domain_error("unmatched case");
    };

    return go(0, 0);
  }
};
