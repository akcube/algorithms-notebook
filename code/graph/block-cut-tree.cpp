/**
 * TODO: 
 * 1. Remove set<int> in tarjans, get complexity back to O(n). I think reverse dfs order works?
 * 2. Cleanup code, less hacky way to identify cut vertices on tree
*/
void tarjans_c(int node, vvi &adj, int p, vi &disc, vi &low, vb &iscut, vvi &components, vi &stack){
    static int timer = 1;
    if(disc[node]) return;
    disc[node] = low[node] = timer++;
    stack.pb(node);

    set<int> special;
    for(auto &to:adj[node]){
        if(to == p) continue;
        if(disc[to]) low[node] = min(low[node], disc[to]);
        else{
            tarjans_c(to, adj, node, disc, low, iscut, components, stack);
            low[node] = min(low[node], low[to]);
            if(p == -1) special.insert(to);
            if(low[to] >= disc[node] and p != -1) {
                components.pb({node});
                while(components.back().back() != to) 
                    components.back().pb(stack.back()), stack.pop_back();
                iscut[node] = true;
            }
        }
    }
    if(p == -1 and sz(special) > 1) {
        for(auto &to:special){
            components.pb({node});
            while(special.find(components.back().back()) == special.end())
                components.back().pb(stack.back()), stack.pop_back();
        }
        iscut[node] = true;
    }
}

// Returns number of cut vertices. v < num_cut_vertices => v is a cut vertex in the tree
int blockCutTree(vvi &adj, vvi &tree, vi &m, vb &iscut){
    int n = sz(adj);
    vi disc(n), low(n), stack;
    m.assign(n, -1);
    tree.assign(2*n, vi());
    iscut.assign(n, false);
    vb vis(n);
    vvi components;
    tarjans_c(0, adj, -1, disc, low, iscut, components, stack);
    if(sz(stack) > 1) components.pb(stack); // If parent is not a cut vertex
    
    int id = 0;
    for(int v = 0; v<n; v++) if(iscut[v]) m[v] = id++;
    int ans = id;
    for(auto &comp:components){
        bool special = true;
        for(auto &v:comp)
            if(!iscut[v]) special = false;

        // If the size of a component is 2 and both vertices are cut vertices then
        // the tree has an edge between these two cut vertices.
        if(special && sz(comp) == 2){    
            tree[m[comp[0]]].pb(m[comp[1]]);
            tree[m[comp[1]]].pb(m[comp[0]]);
        }
        else{
            int comp_id = id++;
            for(auto &v:comp){
                if(!iscut[v]) m[v] = comp_id;
                else {
                    tree[m[v]].pb(comp_id);
                    tree[comp_id].pb(m[v]);
                }
            }
        }
    }
    return ans;
}   