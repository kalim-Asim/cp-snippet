
bool isBipartite(int V, vector<vector<int>> &adj) {
    vector<int> col(V, -1);
    queue<int> q;
    for(int i = 0; i < V; i++) {
        if(col[i] != -1) continue;

        col[i] = 0;
        q.push(i);
        while(!q.empty()) {
            int cur_v = q.front(); q.pop();
            for(auto &child : adj[cur_v]) {
                if(col[child] == -1) {
                    col[child] = 1 - col[cur_v];
                    q.push(child);
                }
                else if(col[child] == col[cur_v]) {
                    return false;
                }
            }
        }
        
    }
    return true;
}


