int up[200001][20];

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
