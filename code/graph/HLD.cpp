/**
 * TODO
 * 1. Stress-test 
 * 2. Switch to bottom-up Segtree
*/

struct HLD{
    const int identity = 0;
    int merge(int a, int b) { return a+b; }

    int n, root, timer = 0, tsz;
    vi size, heavy, top, st, en, tree, dep, par;

    void st_update(int node, int val){
        tree[tsz+node] = val;
        for(int i=(tsz+node)/2; i >= 1; i /= 2)
            tree[i] = merge(tree[2*i], tree[2*i + 1]);
    }

    int st_query(int node, int seg_l, int seg_r, int q_l, int q_r){
        if(seg_l >= q_l && seg_r <= q_r) return tree[node];
        if(seg_l > q_r || seg_r < q_l) return identity;
        int mid = seg_l + (seg_r-seg_l)/2;
        return merge(st_query(2*node, seg_l, mid, q_l, q_r), st_query(2*node+1, mid+1, seg_r, q_l, q_r));
    }

    int query(int a, int b){
        int ans = identity;
        for(; top[a] != top[b]; b = par[top[b]]){
            if(dep[top[a]] > dep[top[b]]) swap(a, b);
            ans = merge(ans, st_query(1, 0, tsz-1, st[top[b]], st[b]));
        }
        if(dep[a] > dep[b]) swap(a, b);
        ans = merge(ans, st_query(1, 0, tsz-1, st[a], st[b]));
        return ans;
    }

    void update(int node, int val){
        st_update(st[node], val);
        st_update(en[node], -val);
    }

    void build(){
        int t = sz(tree);
        tsz = 1 << (32 - __builtin_clz (t - 1));
        tree.resize(2*tsz);
        for(int i=0; i<t; i++) tree[tsz+i] = tree[i];
        for(int i=t; i<tsz; i++) tree[tsz+i] = identity;

        for(int i=tsz-1; i >= 1; i--) 
            tree[i] = merge(tree[2*i], tree[2*i+1]);
    }
    
    void dfs_hvy(int v, vvi &adj, int p){
        top[v] = v;
        for(auto &to:adj[v]){
            if(to == p) continue;
            dep[to] = dep[v] + 1;
            par[to] = v;
            dfs_hvy(to, adj, v);
            size[v] += size[to];
            if(heavy[v] == -1 or size[to] > size[heavy[v]]) heavy[v] = to;
        }
    }

    void dfs_hld(int v, vvi &adj, int p, vi &arr){
        st[v] = timer++; tree.pb(arr[v]);
        
        if(heavy[v] != -1){
            top[heavy[v]] = top[v];
            dfs_hld(heavy[v], adj, v, arr);
        }

        for(auto &to:adj[v]){
            if(to == p or to == heavy[v]) continue;
            dfs_hld(to, adj, v, arr);
        }

        en[v] = timer++; tree.pb(-arr[v]);
    }

    HLD(vvi &adj, int r, vi &arr) : n(sz(adj)), heavy(n, -1), top(n), st(n), en(n), dep(n), par(n) {
        size.assign(n, 1);
        tree.reserve(2*n);
        root = r;
        dfs_hvy(root, adj, -1);
        dfs_hld(root, adj, -1, arr);
        build();
    }
};