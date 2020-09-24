/* Solution Begin */
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>> &matrix, int k)
    {
        if (matrix.size() == 0) return 0;
        struct range_sum_query2d_immutable {
        private:
            vector<vector<int>> prefix;
            int R, C;
        public:
            range_sum_query2d_immutable(vector<vector<int>> &matrix) : R(matrix.size()), C(matrix[0].size())
            {
                assert(R >= 0 && C >= 0);
                prefix.resize(R + 1, vector<int>(C + 1, 0));
                for (int r = 1; r <= R; r++)
                    for (int c = 1; c <= C; c++)
                        prefix[r][c] = prefix[r - 1][c] + prefix[r][c - 1] - prefix[r - 1][c - 1] + matrix[r - 1][c - 1];

            }

            int query(int r1, int c1, int r2, int c2)
            {
                return prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] - prefix[r2 + 1][c1] + prefix[r1][c2];
            }

            int query_max_sum_no_larger_than_k(int k)
            {
                int result = INT_MIN;
                for (int c1 = 0; c1 < C; c1++)  // current-x<=k --> x >= current_sum -k
                    for (int c2 = c1; c2 < C; c2++)
                    {
                        vector<int> sum(R);
                        for (int r = 0; r < R; r++)
                            sum[r] = query(0, c1, r, c2);
                        set<int> prev_sums{0};
                        for (int r = 0; r < R; r++)
                        {
                            int current_sum = sum[r];
                            int diff = current_sum - k;
                            if (diff == 0) return k;
                            auto to_subtract = prev_sums.lower_bound(current_sum - k);
                            if (to_subtract != prev_sums.end()) result = max(result, current_sum - *to_subtract);
                            prev_sums.insert(current_sum);
                        }
                    }
                return result;
            }
        };
        range_sum_query2d_immutable module(matrix);

        int result = module.query_max_sum_no_larger_than_k(k);
        return result;
    };

};
