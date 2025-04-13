

const int N = 1e5;
int depth[N], height[N];
vector<int> g[N];
void dfs(int vertex, int par=0) {
    /* Take action on vertex after
        entering the vertex */
    for (auto &child : g[vertex]) {
        /* Take action on child before
           entering the child node */
        if(child == par) continue;
        depth[child] = depth[vertex] + 1;
        dfs(child, vertex);
        height[vertex] = max(height[vertex], height[child] + 1);
        /* Take action on child after
           exiting child node */
    }
    /* Take action on vertex before 
       exiting the vertex */
}

// DP ON TREES - BASIC
// Computes subtree sum at node i
// including the value of node i and 
// no. of nodes which are even
// and gcd of subtree

int val[N], gc[N];
void dfs_preCompute(int vertex, int par=0) {

    if (vertex % 2 == 0) even_ct[vertex]++;
    subtree_sum[vertex] += vertex;
    for (int child : g[vertex]) {
        if (child == par) continue;
        dfs_preCompute(child, vertex);

        subtree_sum[vertex] += subtree_sum[child];
        even_ct[vertex] += even_ct[child];
        gc[vertex] = __gcd(gc[vertex], gc[child]);
    }
}


