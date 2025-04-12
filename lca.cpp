void dfs(int src, int par, int level = 0) {
  lvl[src] = level;
  for (int child : g[src]) {
    if (child == par) continue;
    dfs(child, par);
  }
}

// binary lifting

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
