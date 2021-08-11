struct Edge{
    int u, v, weight;
    Edge(int from, int to, int w) : u(from), v(to), weight(w) {}
    bool operator<(Edge &other) { return weight < other.weight; }
};

class MST{
private:
    int n, p_cost;
    vector<Edge> edges;
    vector<vector<pair<int, int>>> mst;
    DSU dsu;

    void kruskals(vector<Edge> &edgelist){
        sort(edgelist.begin(), edgelist.end());
        dsu.make(n);
        p_cost = 0;
        for(auto &e:edgelist){
            if(dsu[e.u] == dsu[e.v]) continue;
            dsu.unify(e.u, e.v);
            edges.push_back(e);
            mst[e.u].push_back({e.v, e.weight});
            mst[e.v].push_back({e.u, e.weight});
            p_cost += e.weight;
        }
    }

public:
    
    MST() = default;

    MST(vector<vector<pair<int, int>>> &adj){
        n = (int) adj.size();
        mst.resize(n);
        vector<Edge> edgelist;

        for(int i=0; i<n; i++)
            for(auto &p:adj[i])
                edgelist.push_back(Edge(i, p.first, p.second));

        kruskals(edgelist);
    }

    MST(int size, vector<Edge> &edgelist){
        n = size;
        mst.resize(n);
        kruskals(edgelist);
    }

    int cost() { return p_cost; }
    vector<vector<pair<int, int>>> get_tree() { return mst; }
    vector<Edge> get_edgelist() { return edges; }
};