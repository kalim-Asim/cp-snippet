
const int N = 3 * 1e5 + 10;
struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size.
    // When data[x] >= 0, data[x] is x's parent.
    vector<int> data;
    int components = 0;
    union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }
    void init(int n) {
        data.assign(n, -1);
        components = n;
    }
    int find(int x) {
        return data[x] < 0 ? x : data[x] = find(data[x]);
    }
    int get_size(int x) {
        return -data[find(x)];
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
 
        if (x == y)
            return false;
 
        if (-data[x] < -data[y])
            swap(x, y);
 
        data[x] += data[y];
        data[y] = x;
        components--;
        return true;
    }
};
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
int n, m, members, candidate, connected_component;
vi g[N], parent(N), _size(N);

void make(int v) {
    parent[v] = v;
    _size[v] = 1;
}

int find(int v) {
    if (v == parent[v]) return v;
    // Path Compression
    return parent[v] = find(parent[v]);
}

void Union(int a, int b) {
    a = find(a); 
    b = find(b);
    if (a != b) {
        // Union by size
        if (_size[a] < _size[b]) swap(a, b);
        // bade tree ke andar chota tree
        // bada tree on left(a)
        parent[b] = a;
        _size[a] += _size[b];
        --connected_component;
    }
}

// stores size of component of vertex v
int get_size(int v) {
    if(parent[v] == v) return _size[v];
    else return get_size(parent[v]);
}

int main() {
    int n, k;
    cin >> n >> k;
    connected_component = n;
    for (int i = 0; i <= n; i++) {
        make(i);
    }

    while(k--) {
        int u, v; 
        cin >> u >> v;
        Union(u, v);
    }

    int connected_component2 = 0;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i) connected_component2++;
    } // above and this give same ans
}

