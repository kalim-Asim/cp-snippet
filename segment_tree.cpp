// Range sum query - point update 
// (STANDARD TEMPLATE)
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
            int pos, val; cin >> pos >> val;
            seg.update(0, 0, n - 1, --pos, val);  
        } else if (type == 2) {
            int l, r; cin >> l >> r;
            cout << seg.query(0, 0, n - 1, --l, --r) << "\n";  
        }
    }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */


// range min, gcd, countOfMin query - no updates
struct Node {
    int gcd, mn, cntmn;
};
struct SegmentTree {
    int n;                  
    vector<Node> tree;         
    vector<int> arr;     

    SegmentTree(const vector<int>& a) {
        n = a.size();
        arr = a;
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }
    Node merge(const Node& l, const Node& r) {
        Node res;
        res.mn = min(l.mn, r.mn);
        res.gcd = __gcd(l.gcd, r.gcd);
        if (l.mn == r.mn) res.cntmn = l.cntmn + r.cntmn;
        else res.cntmn = l.mn == res.mn ? l.cntmn : r.cntmn;
        return res;
    }
    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx].mn = arr[l];
            tree[idx].gcd = arr[l];
            tree[idx].cntmn = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx + 1, l, mid);
        build(2 * idx + 2, mid + 1, r);
        tree[idx] = merge(tree[2*idx+1], tree[2*idx+2]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || ql > r)
            return {0, inf, 0};
        if (ql <= l && r <= qr)
            return tree[idx];
        int mid = (l + r) / 2;
        Node left = query(2 * idx + 1, l, mid, ql, qr);
        Node right = query(2 * idx + 2, mid + 1, r, ql, qr);
        return merge(left, right);
    }
};


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// INVERSION COUNT + Compression
// Standard Template(1st one)
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int,int> mp;
    for (int& i: a) cin >> i, mp[i];
    // coordinate compression
    int ptr = 1;
    for (auto &pr : mp) {
        pr.second = ptr++;
    }
    for (int i = 0; i < n; ++i) {
        a[i] = mp[a[i]];
    }

    int mx = *max_element(a.begin(), a.end());
    vector<int> freq(mx+1, 0);

    // for every i, find no. of elements to its left which are greater
    // and no. of elements to its right which are lesser

    int ans = 0;
    vector<int> greater(n), lesser(n);
    SegmentTree seg1(greater), seg2(lesser);
    for (int i = 0; i < n; ++i) {
        // finding greater element to left
        if (a[i]+1 <= mx) {
            greater[i] = seg1.query(0, 0, mx, a[i] + 1, mx);
        }
        seg1.update(0, 0, mx, a[i], 1);
    }

    for (int i = n-1; i >= 0; i--) {
        // finding lesser element to right
        if (a[i]-1 >= 1) {
            lesser[i] = seg2.query(0, 0, mx, 0, a[i]-1);
        }
        seg2.update(0, 0, mx, a[i], 1);
    }

    for (int i = 0; i < n; i++) 
        ans += lesser[i]*greater[i];
    cout << ans << endl;
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

    void updateRange(int ql, int qr, int val) {
        updateRange(0, 0, n - 1, ql, qr, val);
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

    int queryRange(int ql, int qr) {
        return queryRange(0, 0, n - 1, ql, qr);
    }

    int queryRange(int idx, int l, int r, int ql, int qr) {
        propagate(idx, l, r);
        if (r < ql || l > qr) 
            return 0;                    
        if (l >= ql && r <= qr) 
            return tree[idx];           
        int mid = (l + r) / 2;
        return queryRange(2 * idx + 1, l, mid, ql, qr)
             + queryRange(2 * idx + 2, mid + 1, r, ql, qr);
    }

    int queryPoint(int pos) {
        return queryPoint(0, 0, n - 1, pos);
    }

    int queryPoint(int idx, int l, int r, int pos) {
        propagate(idx, l, r);
        if (l == r) return tree[idx];
        int mid = (l + r) / 2;
        if (pos <= mid)
            return queryPoint(2 * idx + 1, l, mid, pos);
        else
            return queryPoint(2 * idx + 2, mid + 1, r, pos);
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
