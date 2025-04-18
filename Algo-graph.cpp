// 1. Topological Sort
struct topoSort {
    const static int N = 1e5 + 5;
    vector<int> vis, indegree;
    vector<int> g[N];

    topoSort() {
        vis.resize(N, 0);
        indegree.resize(N, 0);
    }

    void addEdge(int u, int v) {
        g[u].push_back(v);
    }

    vector<int> bfs(int n) {
        fill(indegree.begin(), indegree.begin() + n, 0);
        for (int i = 0; i < n; ++i) {
            for (auto& it : g[i]) indegree[it]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> ans;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            ans.push_back(node);

            for (auto it : g[node]) {
                indegree[it]--;
                if (indegree[it] == 0) q.push(it);
            }
        }

        return ans;
    }
};
/*
    topoSort ts;
    int n = 6;

    ts.addEdge(5, 2);
    ts.addEdge(5, 0);
    ts.addEdge(4, 0);
    ts.addEdge(4, 1);
    ts.addEdge(2, 3);
    ts.addEdge(3, 1);
    vector<int> topo = ts.bfs(n);
*/


/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 2. DSU
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

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 3. Kruskal - MST

/* dsu template */
void kruskal() {
    cin >> n >> m;

    vector<pair<int ,pair<int,int>>> edges;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> wt;
        edges.push_back({wt, {u, v}});
    }
    sort(edges.begin(), edges.end());

    union_find g(n+1); //1 based

    int totalCost = 0;
    for (auto &V : edges) {
        int wt = V.first, u = V.second.first, v = V.second.second;
        if (g.find(u) == g.find(v)) continue;

        g.unite(u, v);
        totalCost += wt;
        cout << u << ' ' << v << '\n';
    }
  // if graph connected or mst was formed -> g.components==1
    cout << totalCost << endl;
}

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 4. IsCycle - Unweighted graph
// dfs
bool isCycleDfs() {
  function<bool(int, int)> dfs = [&](int v, int par) {
    vis[v] = 1;
    for (auto& u : g[v]) {
        if (!vis[u]) {
            if (dfs(u, v) == true) return true;
        }
        else if (u != par) return true;
    }
    return false;
  };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (dfs(i, -1) == true)
                return true;
        }
    }
    return false;
}
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 5. Is Bipartite
bool isBipartite() {
    vector<int> col(n+1, -1);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (col[i] != -1) continue;
        col[i] = 0;
        q.push(i);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : g[v]) {
                if (col[u] == -1) {
                    col[u] = 1 - col[v];
                    q.push(u);
                }
                else if (col[u] == col[v])  return false;
            }
        }
    }
    return true;
}

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 6. DIJKSTRA
const int N = 1e3 + 10;
vector<pair<int,int>> g[N]; // node , weight
vector<int> vis(N, 0), dist(N, 1e9);
void dijkstra(int source) {
    set<pair<int,int>> st; // weight , node
    st.insert({0, source});
    dist[source] = 0;

    while(st.size() > 0) {
        auto node = *st.begin();
        int v = node.second;
        int dist_v = node.first;
        st.erase(st.begin());

        if(vis[v]) continue;
        vis[v] = 1;

        for(auto child : g[v]) {
            int child_v = child.first;
            int wt = child.second;

            if(dist_v + wt < dist[child_v]) {
                dist[child_v] = dist[v] + wt;
                st.insert({dist[child_v], child_v});
            }
        }
    }
}

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 7. Floyd Warshall
const int N = 510;
const int INF = 1e9+10;
int dist[N][N];
void FloydWarshall() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    int Vertices, Edges;
    cin >> Vertices >> Edges;
    for (int i = 0; i < Edges; ++i) {
        int x, y, wt;
        cin >> x >> y >> wt;
        dist[x][y] = wt;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i<=n; i++) {
            for(int j = 1; j<=n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 8. Euler DFS
int N = 2*1e5;
int timer = 1;
int in[N+1], out[N+1];
vector<int> eulerTour = {-1};
void eulerDfs(int v, int par) {
    in[v] = timer++;
    for (int u : g[v]) {
        if (u == par) continue;
        eulerDfs(u, v);
    }
    out[v] = timer++;
    return;
}

euler(1,-1); // 1 based tree
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 9. 

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    */

// 10.
