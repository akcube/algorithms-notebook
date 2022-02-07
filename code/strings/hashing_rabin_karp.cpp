// Note: Might have overflow bugs, need to stress test. Use with #define int ll just in case.
// Note2: Useful but also memory heavy as it maintains rabinkarp array for all strings.

class hstring{
private:
    int n;
    string s;
    vector<pii> h;
    const static int p1 = 137;
    const static int p2 = 277;
    const static int m1 = 127657753;
    const static int m2 = 987654319;
    static vector<pii> pow_p; 
    static vector<pii> ipow_p;

    void prec(){
        pow_p[0] = ipow_p[0] = {1, 1};
        int ip1 = 11181701;
        int ip2 = 802246288;
        for(int i=1; i<sz(pow_p); i++) {
            pow_p[i].ff = (1ll*pow_p[i-1].ff*p1)%m1;
            ipow_p[i].ff = (1ll*ipow_p[i-1].ff*ip1)%m1;
            pow_p[i].ss = (1ll*pow_p[i-1].ss*p2)%m2;
            ipow_p[i].ss = (1ll*ipow_p[i-1].ss*ip2)%m2;
        }
    }

    void _hash(){
        if(pow_p[0].ff == 0) prec();
        
        n = sz(s);
        h.resize(n+1);
        for(int i=0; i<sz(s); i++){
            h[i+1].ff = (h[i].ff + (1ll*s[i]*pow_p[i].ff)%m1)%m1;
            h[i+1].ss = (h[i].ss + (1ll*s[i]*pow_p[i].ss)%m2)%m2;
        }
    }

public:
    hstring() = default;
    hstring(string &t) : s(t){ _hash(); }
    hstring(string t) : s(t){ _hash(); }

    pii hash() { return h[n]; }
    pii hash(int l, int r) { 
        int fi = ((h[r+1].ff - h[l].ff + m1) * 1ll * ipow_p[l].ff)%m1;
        int se = ((h[r+1].ss - h[l].ss + m2) * 1ll * ipow_p[l].ss)%m2;
        return {fi, se}; 
    }

    size_t size() { return sz(s); }
    string& str() { return s; }

    bool operator ==(hstring &t) { return t.hash() == hash(); }
    friend istream &operator>>(istream &in, hstring &hs) {
        in>>hs.s; hs._hash();
        return in;
    }
};

vector<pii> hstring::pow_p(1e7);
vector<pii> hstring::ipow_p(1e7);
