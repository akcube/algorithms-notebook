#include <dsu.cpp>

struct Edge { int u, v, w; };

template<typename F>
struct EdgeDecompositionTree {
    int root, n;
    vvi adj; // Take reference to this tree to solve
    vector<Edge> &e;
    vi par; // Use for binary lifting
    EdgeDecompositionTree(int n, vector<Edge> &e, F cmp) : n(n), adj(2*n), e(e), par(2*n, -1) {
        vi head(n); iota(all(head), 0);
        vi ord(n-1); iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) { return cmp(e[i], e[j]); });
        reverse(all(ord));
        DSU dsu(n);
        auto add_edge = [&](int v, int p){
            adj[p].pb(v); adj[v].pb(p); 
            par[v] = p; };
        for(auto &eid : ord){
            int u = dsu[e[eid].u], v = dsu[e[eid].v];
            dsu.unify(u, v);
            add_edge(head[u], eid + n); add_edge(head[v], eid + n);
            head[dsu[u]] = eid + n;
        }
        root = n + ord.back();
        par[root] = root;
    }
    pair<vi, vii> flatten(){
        int t = 0;
        vi flat(n);
        vii r(2*n, {INT_MAX, INT_MIN});
        function<void(int,int)> dfs = [&](int v, int p){
            if(v < n) r[v] = {t, t}, flat[t++] = v;
            for(auto &to : adj[v]){
                if(to == p) continue;
                dfs(to, v);
                r[v].ff = min(r[v].ff, r[to].ff);
                r[v].ss = max(r[v].ss, r[to].ss);
            }
        };
        dfs(root, -1);
        return {flat, r};
    }
};