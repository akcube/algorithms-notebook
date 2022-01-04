// Note: Might have overflow bugs, need to stress test. Use with #define int ll just in case.

const static int p1 = 137;
const static int p2 = 277;
const static int m1 = 127657753;
const static int m2 = 987654319;
vector<pii> pow_p; 
vector<pii> ipow_p;

void prec(){
    pow_p.resize(1e7);
    ipow_p.resize(1e7);
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

pii _hash(string &s){
    if(pow_p.empty()) prec();
    int n = sz(s);
    vii h(2, {0, 0});
    int p = 0;
    for(int i=0; i<n; i++, p^=1){
        h[p^1].ff = (h[p].ff + (1ll*s[i]*pow_p[i].ff)%m1)%m1;
        h[p^1].ss = (h[p].ss + (1ll*s[i]*pow_p[i].ss)%m2)%m2;
    }
    return h[p^1];
}