// CSES - Company queries 1
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 200000;
int up[N+1][20];
vector<vector<int>> g;
void binary_lifting(int src, int par = -1) {
  up[src][0] = par;
  for (int i = 1; i < 20; i++) {
    if (up[src][i-1] != -1) up[src][i] = up[up[src][i-1]][i-1];
    else up[src][i] = -1;
  }

  for (int child : g[src]) {
    if (child == par) continue;
    binary_lifting(child, src);
  }
}
int query(int node, int jump_required) {
  if (node == -1 || jump_required == 0) 
      return node;

  for (int i = 19; i >= 0; i--) {
    if (jump_required >= (1 << i)) {
      return query(up[node][i], jump_required - (1 << i));
    }
  }  
}
void solve(int tt, int tc) {
    int n, q;
    cin >> n >> q;
    g.resize(n+1);
    for (int i = 2; i <= n; i++) {
        int u; cin >> u;
        g[u].push_back(i);
        g[i].push_back(u);
    }
    binary_lifting(1);
    while(q--) {
        int u, k;
        cin >> u >> k;
        cout << query(u, k) << '\n';
    }
}

signed main(){
    solve();
    return 0;
}
