struct Edge{
    int u, v;
    bool deleted;
};

// Input code
vector<Edge> edges(n-1);
vvi adj(n);
for(int i=0; i < n-1; i++){
    int u, v; cin >> u >> v; u--, v--;
    edges[i] = {u, v, false};
    adj[u].pb(i);
    adj[v].pb(i);
}

// ------------------------------ Centroid Code ------------------------------
vi size(n), level(n); // aux stuff
vvi pre(21, vi(n)); // f(c_level, node)
vi cpar(n, -1); // centroid tree representation
auto g = [&](Edge &e, int v) { return v ^ e.u ^ e.v; };

auto add_centroid_edge = [&](int p, int c){
    cpar[c] = p;
};

function<void(int,int,int)> preprocess = [&](int v, int p, int level){
    for(auto &eid:adj[v]){
        auto &e = edges[eid];
        int to = g(e, v);
        if(e.deleted or to == p) continue;
        preprocess(to, v, level);
    }
};

function<int(int, int)> decompose = [&](int v, int p){
    // 1 - Compute new subtree sizes
    function<void(int, int)> subtree_comp = [&](int v, int p){
        size[v] = 1;
        for(auto &eid : adj[v]){
            auto &e = edges[eid];
            int to = g(e, v);
            if(e.deleted or to == p) continue;
            subtree_comp(to, v);
            size[v] += size[to];
        }
    };
    subtree_comp(v, -1);

    // 2 - Identify subtree centroid
    function<int(int, int)> get_centroid = [&](int u, int p){
        for(auto &eid : adj[u]){
            auto &e = edges[eid];
            int to = g(e, u);
            if(e.deleted or to == p) continue;
            if(size[to] > size[v]/2) return get_centroid(to, u);
        }
        return u;
    };
    int centroid = get_centroid(v, -1);
    if(p != -1) level[centroid] = level[p] + 1;

    // 3 - Compute f(centroid, u) \forall u \in st(centroid)
    preprocess(centroid, -1, level[centroid]);

    // 4 - Build the rest of the tree
    for(auto &eid : adj[centroid]){
        auto &e = edges[eid];
        int to = g(e, centroid);
        if(e.deleted) continue;
        e.deleted = true;
        int c = decompose(to, centroid);
        add_centroid_edge(centroid, c);
    }
    return centroid;
};
// ------------------------------ Centroid Code ------------------------------
int root = decompose(0, -1);