class RangeUpdateTree{
private: 
    int n;
    vector<int> tree;
    int identity;

    int merge(int a, int b){
        return a + b;
    }

    int __query(int q){
        int accum = identity;
        for(int i=n+q; i > 0; i /= 2){
            accum = merge(tree[i], accum);
        }
        return accum;
    }

    void __update(int node, int seg_l, int seg_r, int q_l, int q_r, int val){
        if(seg_l > q_r || seg_r < q_l) return;
        if(seg_l >= q_l && seg_r <= q_r) {
            tree[node] += val;
            return;
        }
        int mid = seg_l + (seg_r-seg_l)/2;
        __update(2*node, seg_l, mid, q_l, q_r, val);
        __update(2*node+1, mid+1, seg_r, q_l, q_r, val);
    }

    void build(vector<int> &arr){
        n = 1 << (32 - __builtin_clz ((int)arr.size() - 1));
        tree.resize(2*n);
        for(int i=0; i<arr.size(); i++)
            tree[n+i] = arr[i];
    }

public:
    RangeUpdateTree(vector<int> &arr, int id){
        identity = id;
        build(arr);
    }

    int query(int pos){
        return __query(pos);
    }

    void update(int l, int r, int value){
        __update(1, 0, n-1, l, r, value);
    }
};