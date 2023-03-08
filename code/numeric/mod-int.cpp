template<const int mod>
struct mint {
    mint(int x = 0) : val((x % mod + mod) % mod) {}
    mint& operator+=(const mint &b) { val += b.val; val -= mod * (val >= mod); return *this; }
    mint& operator-=(const mint &b) { val -= b.val; val += mod * (val < 0); return *this; }
    mint& operator*=(const mint &b) { val = 1ll * val * b.val % mod; return *this; }
    mint& operator/=(const mint &b) { return *this *= b.inv(); }
    mint inv() const {
        int x = 1, y = 0, t;
        for(int a=val, b=mod; b; swap(a, b), swap(x, y))
            t = a/b, a -= t * b, x -= t * y;
        return mint(x);
    }
    friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
    friend bool operator!=(const mint &a, const mint &b) { return a.val != b.val; }
    friend std::ostream& operator<<(std::ostream &os, const mint &a) { return os << a.val; }
    int val;
};
using Mint = mint<MOD>;
