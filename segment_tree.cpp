// range max query - no updates
struct SegmentTree {
    static const int N = 1e5;
    int a[N], seg[4 * N];

    void build(int ind, int lo, int hi) {
        if (lo == hi) {
            seg[ind] = a[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * ind + 1, lo, mid);
        build(2 * ind + 2, mid + 1, hi);
        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int lo, int hi, int l, int r) {
        if (lo >= l && hi <= r) return seg[ind];
        if (hi < l || lo > r) return INT_MIN;

        int mid = (lo + hi) / 2;
        int left = query(2 * ind + 1, lo, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, hi, l, r);
        return max(left, right);
    }
};

int main() {
    SegmentTree st;
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> st.a[i];

    st.build(0, 0, n - 1);

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << st.query(0, 0, n - 1, l, r) << "\n";
    }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// Range sum query - point update
struct SegmentTree {
    int n;
    vector<int> a, tree;

    SegmentTree(int _n) : n(_n) {
        a.resize(n);
        tree.resize(4 * n, 0);
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx + 1, l, mid);
        build(2 * idx + 2, mid + 1, r);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    int query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[idx];
        int mid = (l + r) / 2;
        int left = query(2 * idx + 1, l, mid, ql, qr);
        int right = query(2 * idx + 2, mid + 1, r, ql, qr);
        return left + right;
    }

    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(2 * idx + 1, l, mid, pos, val);
        else
            update(2 * idx + 2, mid + 1, r, pos, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    SegmentTree st(n);
    for (int i = 0; i < n; i++) {
        cin >> st.a[i];
    }

    st.build(0, 0, n - 1);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, u;
            cin >> k >> u;
            st.update(0, 0, n - 1, k - 1, u);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(0, 0, n - 1, l - 1, r - 1) << '\n';
        }
    }
}

