
// DIJKSTRA

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

