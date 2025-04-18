
const int MAXN = 1e5 + 5;
const int mod = 998244353;
int fac[MAXN + 1];
int inv[MAXN + 1];

void modadd(int &a , int b) {
    a = ((a % mod) + (b % mod)) % mod;
}
void modsub(int &a , int b) {
    a = ((a % mod) - (b % mod) + mod) % mod;
}
void modmul(int &a , int b) {
    a = ((a % mod) * (b % mod)) % mod;
}
int moddiv(int a, int b) {
    return (int)((1LL * (a % mod) * exp(b % mod, mod - 2)) % mod);
}
int inv(int a, int p = mod - 2) {
    if(p == 0) return 1;
    if(p & 1) return (a * inv(a, p - 1)) % mod;
 
    int k = inv(a, p / 2);
    return (k * k) % mod;
}
 
int exp(int x, int n, int mod) {
    x %= mod;
    int res = 1; 
    while (n > 0) {
        if (n % 2 == 1) res = res * x % mod;
        x = x * x % mod; 
        n /= 2;
    }
    return res % mod;
}
void factorial(){
    fac[0] = 1;
    for(int i = 1; i <= MAXN; i++)  fac[i] = fac[i - 1] * i % mod; 
}
void inverses() {
    inv[MAXN] = exp(fac[MAXN], mod - 2, mod);
    for (int i = MAXN; i >= 1; i--) inv[i - 1] = inv[i] * i % mod; 
}
int nCr(int n, int r) { 
    return (r > n ? 0ll : (fac[n] * inv[r] % mod * inv[n - r] % mod) % mod) ;
}




//     SIEVE PRIME NO. 
const int N = 1e6;
vector<bool> is_prime(N,1);
void sieve(){
    for (int i = 2; i*i<=N; i++){
        if(is_prime[i]){
            for (int j = i*i; j<=N; j+=i){
                is_prime[j] = 0;
            }
        }
    }
 }

//     PRIME FACTORISATION
vector<pii> fact;
void primeFact(int n){
    for (int i = 2; i * i <= n; i++){
        if (n % i) continue;
        int cnt = 0;
        while(n % i == 0) cnt++, n /= i;
        fact.pb({i , cnt});
    }
    if (n > 1) fact.pb({n , 1});
 }

//    PerfectSquare BinarySearch
bool isPerfectSquare(int n)
{
    if (n <= 1) return true;
    int left = 1, right = sqrt(n);
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int square = mid * mid;
        if (square == n) return true;
        else if (square < n) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

//   Of Perfect Square Only
int SquareRoot(int n)
{
    if(n <= 1) return n;
    int l = 1, r = sqrt(n), ans{};
    while(l <= r)
    {
        int mid = (l + r) / 2;
        int sq = mid * mid;
        if(sq == n) {ans = mid;break;}
        else if(sq < n) l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}


