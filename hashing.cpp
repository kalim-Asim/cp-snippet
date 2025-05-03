

// Hash function for pairs
struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1); // Combine the two hashes
    }
};
 
struct Hash {
    const int Base1 = 5689; 
    const int Base2 = 8861;  
 
    vector<pii> hashes, powers; 
 
    Hash(const string &s) {
        int n = s.size();
        hashes.assign(n + 1, {0, 0});
        powers.assign(n + 1, {1, 1});
 
        for (int i = 0; i < n; i++) {
            hashes[i + 1] = {
                (1LL * hashes[i].first * Base1 + (s[i] - 'a' + 1)) % MOD,
                (1LL * hashes[i].second * Base2 + (s[i] - 'a' + 1)) % MOD
            };
 
            powers[i + 1] = {
                (1LL * powers[i].first * Base1) % MOD,
                (1LL * powers[i].second * Base2) % MOD
            };
        }
    }
 
    // Retrieve the hash of a substring [l, r] (1-based indexing)
    pair<int, int> getHash(int l, int r) {
        l++; r++; // Convert to 1-based indexing
 
        int hash1 = (hashes[r].first - 1LL * hashes[l - 1].first * powers[r - l + 1].first % MOD + MOD) % MOD;
        int hash2 = (hashes[r].second - 1LL * hashes[l - 1].second * powers[r - l + 1].second % MOD + MOD) % MOD;
 
        return {hash1, hash2};
    }
};
