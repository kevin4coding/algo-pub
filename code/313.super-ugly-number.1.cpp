class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    const int m = std::size(primes);

    // yet to find a recursinve approach to this.
    auto make_f = [&](std::vector<int> f = {}) {
      f.resize(n, INT_MAX);
      std::vector<int> last(m, 0);
      f[0] = 1;
      for(int i = 1; i < n; i++) {
        for(int k = 0; k < m; k++) {
          f[i] = min(f[i], f[last[k]] * primes[k]);
        }
        for(int k = 0; k < m; k++) {
          if(f[i] == f[last[k]] * primes[k]) last[k]++;
        }
      }
      return f;
    };

    const auto f = make_f();
    
    return f[n - 1];
  }
};
