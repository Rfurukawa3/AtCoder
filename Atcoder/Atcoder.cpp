#include <bits/stdc++.h>
using namespace std;
struct ios_accelerate { ios_accelerate() { ios::sync_with_stdio(false); cin.tie(nullptr); } } CALL;

#define REP(i, n) for(auto (i) = (n)*0; (i) < (n); (i)++)
#define RNG(i, a, b) for(auto (i) = (a); (i) < (b); (i)++)
#define RBF(i, v) for(auto& (i) : (v))
#define ALL(x) (x).begin(), (x).end()

using LL = long long;
using UL = unsigned long;
using ULL = unsigned long long;
template<typename T> using V = vector<T>;
template<typename T> using VV = vector<vector<T>>;
template<typename T> using P = pair<T, T>;

const double PI = 3.141592653589793;
const int MOD = 1000000007;
const LL INF64 = static_cast<LL>(1e18) + 2;
const int INF = static_cast<int>(1e9) + 2;

template<typename T> inline void upsort(vector<T>& x) { sort(x.begin(), x.end()); }
template<typename T> inline void downsort(vector<T>& x) { sort(x.begin(), x.end(), greater<T>()); }
template<typename T> inline void col(T x) { cout << x << '\n'; }
template<> inline void col(double x) { cout << fixed << setprecision(12) << x << '\n'; }

int64_t mod_pow(int64_t x, int64_t n, int64_t mod) {
	int64_t res = 1;
	while (n > 0) {
		if (n & 1) res = res * x % mod; // 最下位ビットが立っているときにx^(2^i)をかける
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}

std::vector<int64_t> inv, fact_inv, com;
void combination_init(int64_t k_max, int64_t mod, int64_t n = -1) {
	int64_t size = k_max + 5;
	inv = std::vector<int64_t>(size);
	fact_inv = std::vector<int64_t>(size);
	inv[1] = 1;
	fact_inv[0] = fact_inv[1] = 1;
	for (int64_t i = 2; i < size; i++) {
		inv[i] = mod - inv[mod % i] * (mod / i) % mod;
		fact_inv[i] = fact_inv[i - 1] * inv[i] % mod;
	}
	if (n >= 0) {
		com = std::vector<int64_t>(size);
		com[0] = 1;
		for (int64_t i = 1; i < size; i++) {
			com[i] = com[i - 1] * ((n - i + 1) * inv[i] % mod) % mod;
		}
	}
}

signed main() {
	LL n, a, b;
	cin >> n >> a >> b;

	LL ans = mod_pow(2, n, MOD);
	combination_init(b, MOD, n);
	LL ncb = com[b];
	LL nca = com[a];
	ans = ans - nca - ncb - 1;
	while (ans < 0) {
		ans += MOD;
	}

	col(ans);
	return 0;
}
