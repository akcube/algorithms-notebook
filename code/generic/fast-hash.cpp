struct chash {
    const uint64_t RANDOM = (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned hash32(unsigned x) { // For 4 byte datatypes only
        x = (x ^ (x >> 16)) * 0x45d9f3b;
        x = (x ^ (x >> 16)) * 0x45d9f3b;
        return x ^ (x >> 16);
    }
    static uint64_t splitmix64(uint64_t x) { // For 8 byte datatypes
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    template<typename T>
    uint64_t operator()(T x) const { 
        return sizeof(x) <= 4 ? hash32(unsigned(x ^ RANDOM)) : (splitmix64(x) ^ RANDOM); 
    }
};

using hash_table = gp_hash_table<int, int, chash>;