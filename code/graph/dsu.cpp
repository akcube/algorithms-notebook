struct DSU{
    vi dsu, szx;

    DSU() = default;
    DSU(int n) : dsu(n), szx(n, 1) { 
        for(int i=0; i<n; i++) dsu[i] = i;
    }
    
    int parent(int i){
        if(dsu[i]==i) return i;
        else return dsu[i] = parent(dsu[i]);
    }

    int size(int i) { return szx[parent(i)]; }
    int operator[](int i){ return parent(i); }

    void unify(int a, int b){
        a = parent(a);
        b = parent(b);
        if(szx[a] < szx[b]) swap(a, b);
        if(a!=b) dsu[b] = a, szx[a] += szx[b];
    }
};