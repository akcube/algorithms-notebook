template<typename... Ts, size_t... Is, typename F>
void __op(index_sequence<Is...>, tuple<Ts...>& a, const tuple<Ts...>& b, F op) { ((get<Is>(a) = op(get<Is>(a), get<Is>(b))), ...); }
#define OVERLOAD(OP, F) \
template<typename... Ts> auto& operator OP##=(tuple<Ts...> &a, const tuple<Ts...> &b) { __op(index_sequence_for<Ts...>(), a, b, F<>{}); return a; } \
template<typename... Ts> auto operator OP(const tuple<Ts...> &a, const tuple<Ts...> &b) { auto c = a; c OP##= b; return c; }
OVERLOAD(+, plus) OVERLOAD(-, minus) OVERLOAD(*, multiplies) OVERLOAD(/, divides)

const int MAXN = 2e5+10; // *
constexpr int NUM_HASHES = 2; // *
constexpr array<int, NUM_HASHES> mods = {127657753, 987654319}; // *
template <size_t N = NUM_HASHES>
constexpr auto mint_ntuple(const int &v) {
    return [&]<size_t... Is>(index_sequence<Is...>) { return make_tuple(mint<mods[Is]>(v)...); }(make_index_sequence<N>{}); }

using HT = decltype(mint_ntuple(0));
HT p1 = {137, 277}; // *

HT pp[MAXN], ipp[MAXN];
void prec(){
    pp[0] = ipp[0] = mint_ntuple(1);
    HT ip1 = pp[0] / p1;
    for(int i=1; i < MAXN; i++){
        pp[i] = pp[i-1] * p1;
        ipp[i] = ipp[i-1] * ip1;
    }
}

template<typename T>
struct hstring{
    vector<HT> h;
    hstring() = default;
    hstring(T &v) : h(sz(v)+1) {
        for(int i=0; i < sz(v); i++) h[i+1] = h[i] * p1 + mint_ntuple(v[i]);
    }
    HT hash(int l, int r){ return h[r+1] - h[l] * p[r-l+1]; }
    HT hash() { return h.back(); }
};
