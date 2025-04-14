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
    vector<int> tree;         
    vector<int> arr;     

    SegmentTree(const vector<int>& a) {
        n = a.size();
        arr = a;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx + 1, l, mid);
        build(2 * idx + 2, mid + 1, r);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
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

    int query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || ql > r)
            return 0;
        if (ql <= l && r <= qr)
            return tree[idx];
        int mid = (l + r) / 2;
        int leftSum = query(2 * idx + 1, l, mid, ql, qr);
        int rightSum = query(2 * idx + 2, mid + 1, r, ql, qr);
        return leftSum + rightSum;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    SegmentTree seg(a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, u;
            cin >> k >> u;
            seg.update(0, 0, n - 1, k - 1, u);  
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            cout << seg.query(0, 0, n - 1, l - 1, r - 1) << "\n";  
        }
    }
}



/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// range update queries - lazy propagation
/*
    Given an array of n integers, your task is to process q queries of the following types:
    increase each value in range [a,b] by u
    what is the value at position k?
*/

struct SegmentTree {
    int n;  
    vector<int> tree; 
    vector<int> lazy;  

    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void build(const vector<int>& arr, int idx, int l, int r) {
        if(l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * idx + 1, l, mid);
        build(arr, 2 * idx + 2, mid + 1, r);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    void propagate(int idx, int l, int r) {
        if (lazy[idx] != 0) {
            tree[idx] += (r - l + 1) * lazy[idx];
            if(l != r) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void updateRange(int idx, int l, int r, int ql, int qr, int val) {
        propagate(idx, l, r);
        if (r < ql || l > qr) return;
        if (l >= ql && r <= qr) {
            tree[idx] += (r - l + 1) * val;
            if(l != r) {
                lazy[2 * idx + 1] += val;
                lazy[2 * idx + 2] += val;
            }
            return;
        }

        int mid = (l + r) / 2;
        updateRange(2 * idx + 1, l, mid, ql, qr, val);
        updateRange(2 * idx + 2, mid + 1, r, ql, qr, val);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    int queryPoint(int idx, int l, int r, int pos) {
        propagate(idx, l, r);
        if (l == r) return tree[idx];
        int mid = (l + r) / 2;
        if (pos <= mid) return queryPoint(2 * idx + 1, l, mid, pos);
        else return queryPoint(2 * idx + 2, mid + 1, r, pos);
    }
};

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {  
            int a, b, u;
            cin >> a >> b >> u;
            segTree.updateRange(0, 0, n - 1, a - 1, b - 1, u);
        } else {  
            int k;
            cin >> k;
            cout << segTree.queryPoint(0, 0, n - 1, k - 1) << "\n";
        }
    }
}
