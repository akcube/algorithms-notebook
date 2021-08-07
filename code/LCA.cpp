void mark_parents(int node, vvi &adj, vvi &lift, int p, vi &depth){
    for(auto x:adj[node]){
        if(x==p) continue;
        depth[x] = depth[node]+1;
        mark_parents(x, adj, lift, node, depth);
        lift[x][0] = node;
    }
}

int getLCA(int a, int b, vvi &tree, vvi &lift, vi &depth){
    if(depth[a]<depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for(int i=31; i>=0; i--)
        if(diff & (1<<i))
            a = lift[a][i];
    if(a==b) return a;

    for(int i=31; i>=0; i--)
        if(lift[a][i] != lift[b][i])
            a = lift[a][i], b = lift[b][i];

    return lift[a][0];
}

void precomp_LCA(vvi &tree, vi &depth, vvi &lift, int start){
    int n = (int) tree.size();
    lift.assign(n, vi(32, start));
    depth.assign(n, 0);
    depth[start] = 0;
    mark_parents(start, tree, lift, -1, depth);
    for(int i=1; i<32; i++)
        for(int j=0; j<n; j++)
            lift[j][i] = lift[lift[j][i-1]][i-1];
}