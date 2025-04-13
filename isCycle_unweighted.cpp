
bool dfs(int v, int parent, vector<int> vis[], vector<int> adj[]) {
    vis[v] = 1;

    for (auto& u : adj[v]) {
        if (!vis[u]) {
            if (dfs(u, v, vis, adj) == true) 
                return true;
        }
        else if (u != parent)
            return true;
    }

    return false;
}

bool isCycle(int V, vector<int> adj[]) {
    int vis[V] = {0};
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            if (dfs(i, -1, vis,adj) == true)
                return true;
        }
    }
    return false;
}

