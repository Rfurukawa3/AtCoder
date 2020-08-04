#include <bits/stdc++.h>
using namespace std;
struct ios_accelerate { ios_accelerate() { ios::sync_with_stdio(false); cin.tie(nullptr); } } CALL;

#define REP(i, n) for(auto (i) = (n)*0; (i) < (n); (i)++)
#define RNG(i, a, b) for(auto (i) = (a); (i) < (b); (i)++)
#define RBF(i, v) for(auto& (i) : (v))
#define ALL(x) (x).begin(), (x).end()

using LL = long long;
using UL = unsigned;
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

template<typename T> T gcd(T a, T b) {
	if (a < b) return gcd(b, a);
	T r;
	while ((r = a % b)) {
		a = b;
		b = r;
	}
	return b;
}

std::vector<std::pair<LL, LL>> prime_factor;
template<typename T> void prime_factorization(T num) {
	T L = static_cast<T>(ceil(sqrt(num)));
	for (T x = 2; x <= L; x++) {
		bool flg = false;
		while (num % x == 0) {
			if (flg) prime_factor.back().second++;
			else prime_factor.emplace_back(make_pair(x, 1));
			flg = true;
			num /= x;
		}
		if (num == 1) break;
	}
	if (num > 1) prime_factor.emplace_back(make_pair(num, 1));
}

signed main() {
	LL a, b;
	cin >> a >> b;
	
	LL c = gcd(a, b);
	prime_factorization(c);
	LL ans = prime_factor.size() + 1;
	col(ans);
	return 0;
}