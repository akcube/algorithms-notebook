/**
 * TODO
 * 1. Stress-test 
 * NOTE
 * 1. When handling edge weights, REMEMBER to exclude LCA.
 *      - in query(a, b), change the last st query to st[a]+1, st[b]
*/

struct HLD{
    const int identity = 0;
    int merge(int a, int b) { return a+b; }

    int n, root, timer = 0, t;
    vi size, heavy, top, st, en, tree, dep, par;

    void st_update(int v, int val){
        for(tree[v+=t] = val; v > 1; v >>= 1)
            tree[v>>1] = merge(tree[v], tree[v^1]);
    }

    int st_query(int l, int r){
        int res = identity;
        for(l += t, r += t; l <= r; l>>=1, r>>=1){
            if(l == r) return merge(res, tree[l]);
            if(l&1) res = merge(res, tree[l++]);
            if(!(r&1)) res = merge(res, tree[r--]);
        }
        return res;
    }

    int query(int a, int b){
        int ans = identity;
        for(; top[a] != top[b]; b = par[top[b]]){
            if(dep[top[a]] > dep[top[b]]) swap(a, b);
            ans = merge(ans, st_query(st[top[b]], st[b]));
        }
        if(dep[a] > dep[b]) swap(a, b);
        ans = merge(ans, st_query(st[a], st[b]));
        return ans;
    }

    void update(int node, int val){
        st_update(st[node], val);
        st_update(en[node], -val);
    }

    void build(){
        t = sz(tree);
        tree.resize(2*t);
        for(int i=0; i<t; i++) tree[t+i] = tree[i];
        for(int i=t-1; i >= 1; i--) 
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