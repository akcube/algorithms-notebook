/**
 * Terrible temporary use if emergency type segtree
 * Do NOT use unless absolutely necessary
 */
template <typename T, typename M, typename F>
struct Segtree{
    int n;
    vector<T> tree, lazy;
    T identity;
    M merge;
    F l_op;

    Segtree(vector<T> &arr, T id, F _m) : n(sz(arr)), identity(id), merge(_m) {
        tree.resize(2*n), lazy.assign(n, identity);
        for(int i=0; i<n; i++) tree[n+i] = arr[i];
        for(int i=n-1; i>=1; i--) 
            tree[i] = merge(tree[2*i], tree[2*i+1]);
    }

    void apply(int v, T val){
        l_op(val, tree[v]);
        if(v < n) l_op(val, d[v]);
    }

    void build(int v){
        for( ;v > 1; v >>= 1)
            t[v] = l_op(lazy[v], merge(t[v<<1], t[v<<1|1]));
    }

    void push(int v){
        for(int s=h; s > 0; s--){
            int p = v >> s;
            apply(p<<1, lazy[p]);
            apply(p<<1|1, lazy[p]);
            lazy[p] = identity;
        }
    }

    T query(int l, int r){
        l += n, r += n;
        push(l), push(r);
        T res = identity;
        for(; l <= r; l>>=1, r>>=1){
            if(l == r) return merge(res, tree[l]);
            if(l&1) res = merge(res, tree[l++]);
            if(!(r&1)) res = merge(res, tree[r--]);
        }
        return res;
    }

    void update(int l, int r, T value){
        l += n, r += n;
        int l0 = l, r0 = r;
        for(; l <= r; l>>=1, r>>=1){
            if(l == r) { apply(l, value); break; }
            if(l&1) apply(l++, value);
            if(!(r&1)) apply(r--, value);
        }
        build(l0), build(r0);
    }
};