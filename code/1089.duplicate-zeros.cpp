class Solution {
 public:
  void duplicateZeros(vector<int>& arr) {
    const int n = std::size(arr);

    std::function<void(int, int)> go = [&](int i, int j) {
      if (i == j)
        return;
      else if (j > n and arr[i] == 0) {
        go(i - 1, j - 2);
      }
      else if (j == n and arr[i] == 0) {
        arr[n - 1] = 0;
        go(i - 1, j - 2);
      }
      else if (j < n and arr[i] == 0) {
        arr[j] = arr[j - 1] = arr[i];
        go(i - 1, j - 2);
      }
      else if (j >= n and arr[i] != 0) {
        go(i - 1, j - 1);
      }
      else if (j < n and arr[i] != 0) {
        arr[j] = arr[i];
        go(i - 1, j - 1);
      }
    };

    go(n - 1, n - 1 + std::count(std::begin(arr), std::end(arr), 0));
  }
};


