// CSES - company queries 2

const int N = 200000;
int up[N+1][20];

void dfs(int v, int par, int level = 0) {
  lvl[v] = level;
  for (int u : g[v]) {
    if (u == par) continue;
    dfs(u, v);
  }
}

void binary_lifting(int v, int par = -1) {
  up[v][0] = par;
  for (int i = 1; i < 20; i++) {
    if (up[v][i-1] != -1) up[v][i] = up[up[v][i-1]][i-1];
    else up[v][i] = -1;
  }

  for (int u : g[v]) {
    if (u == par) continue;
    binary_lifting(u, src);
  }
}

int lift_node(int v, int jump) {
  for (int i = 19; i >= 0; i--) {
    if (jump == 0 || v == -1) break;
    if (jump >= (1<<i)) {
      jump -= (1<<i);
      v = up[v][i];
    }
  }
  return v;
}

int LCA(int u, int v) { // logn
  if (lvl[u] < lvl[v]) swap(u, v);
  u = lift_node(u, lvl[u] - lvl[v]);
  if (u == v) return u;
  for (int i = 19; i >= 0; i--) {
    if (up[u][i] != up[v][i]) {
      u = up[u][i];
      v = up[v][i];
    }
  }
  return lift_node(u, 1);
}

// just for show - binary search approach
int LCA2(int u, int v) { // (Logn)*(Logn)
  if (lvl[u] < lvl[v] swap(u, v);
  u = lift_node(u, lvl[u] - lvl[v]);

  int lo = 0, hi = lvl[u];
  while(lo != hi) {
    int mid = (lo + hi) / 2;
    int x1 = lift_node(u, mid);
    int x2 = lift_node(v, mid);
    if (x1 == x2) hi = mid;
    else lo = mid + 1;
  }
  return lift_node(u, lo);
}
