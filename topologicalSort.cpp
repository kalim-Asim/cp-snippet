
const int N = 1e5 + 5;
vector<int> vis(N, 0);
vector<int> g[N];
vector<int> indegree(N);
// DFS
void dfs (int node, stack<int>& st) {
    vis[node] = 1;
    for (auto& child : g[node]) {
        if (!vis[child]) {
            dfs(child, st);
        }
    }
    st.push(node);
}

vector<int> toposort(int n) {
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, st);
        }
    }

    vector<int> ans;
    while(!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}



// BFS (kahn's algo)
vector<int> toposort(int n) {
    for (int i = 0; i < n; ++i) {
        for (auto& it: g[it]) indegree[it]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if(indegree[i] == 0) q.push(i);
    }

    vector<int> ans;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (auto it: g[node]) {
            indegree[it]--;
            if (indegree[it] == 0) q.push(it);
        }
    }

    return ans;
}

