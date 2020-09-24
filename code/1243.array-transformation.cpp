class Solution {
 public:
  vector<int> transformArray(vector<int>& arr) {

    const int n = std::size(arr);
    
    std::function<std::vector<int>(void)> transform = [&n, &transform, delta = std::vector<int>(n, 0), arr = arr]() mutable {
      for (int i = 1; i < n - 1; ++i) {
        if (std::max(arr[i - 1], arr[i + 1]) < arr[i])
          delta[i] = -1;
        else if (std::min(arr[i - 1], arr[i + 1]) > arr[i])
          delta[i] = 1;
      }
      if (std::find_if(std::begin(delta), std::end(delta), [](int x) { return x != 0; }) != std::end(delta)) {
        for (int i = 0; i < n; ++i) {
          arr[i] += delta[i];
        }
        std::fill(std::begin(delta), std::end(delta), 0);
        return transform();
      }
      else {
        return arr;
      }
    };

    return transform();
  }
};
