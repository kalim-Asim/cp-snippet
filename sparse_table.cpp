// Build GCD sparse table
// gcd for a range
class SparseTable_gcd {
  int n, logn;
  vector<vector<int>> st;
  public:
  SparseTable_gcd(const vector<int>& nums) {
        n = nums.size();
        logn = 32 - __builtin_clz(n);
        st.assign(n, vector<int>(logn));

        for (int i = 0; i < n; ++i)
            st[i][0] = nums[i];

        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 0; i + (1 << j) <= n; ++i)
                st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) const { // 0-based
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);
        return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
    }
};
