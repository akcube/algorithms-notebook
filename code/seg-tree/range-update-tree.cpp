template <typename T, typename F>
struct RangeUpdateTree{
    int n; vector<T> tree;
    T identity; F merge;
    RangeUpdateTree(vector<T> &arr, T id, F _m) : n(sz(arr)), identity(id), merge(_m), tree(2*n){
        for(int i=0; i<n; i++) tree[n+i] = arr[i];
    }
    void update(int l, int r, T value){
        for(l += n, r += n; l <= r; l>>=1, r>>=1){
            if(l==r) { tree[l] = merge(value, tree[l]); break; }
            if(l&1) tree[l] = merge(value, tree[l]), l++;
            if(!(r&1)) tree[r] = merge(value, tree[r]), r--;
        }
    }
    T query(int v){
        T res = tree[v+=n];
        for(; v > 1; v >>= 1) res = merge(res, tree[v>>1]);
        return res;
    }
};

// Usage
auto merge = [&](int a, int b) { return min(a, b); };
RangeUpdateTree<int, decltype(merge)> st(arr, INT_MAX, merge);