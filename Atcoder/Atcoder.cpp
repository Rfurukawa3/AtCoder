#include <bits/stdc++.h>
using namespace std;
struct ios_accelerate { ios_accelerate() { ios::sync_with_stdio(false); cin.tie(nullptr); } } CALL;

#define REP(i, n) for(int i = 0; i < n; i++)
#define RNG(i, a, b) for(int i = a; i < b; i++)
#define RBF(i, v) for(auto& i : v)
#define ALL(x) x.begin(), x.end()

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

signed main()
{	
	ULL n;
	string x;
	cin >> n >> x;

	ULL one0 = 0;
	for (ULL i = 0; i < n; i++) {
		if (x[i] == '1') one0++;
	}
	bool cnt0 = false;
	ULL one1 = one0 + 1, one_1 = 1;
	if (one0 > 1) one_1 = one0 - 1;
	else cnt0 = true;

	VV<ULL> mods(2, V<ULL>(n, 0));
	ULL t1 = 1, t_1 = 1;
	for (ULL i = 0; i < n; i++) {
		mods[0][i] = t_1 % one_1;
		mods[1][i] = t1 % one1;
		t_1 = t_1 * 2 % one_1;
		t1 = t1 * 2 % one1;
	}

	ULL mod_1 = 0, mod1 = 0;
	for (ULL i = 0; i < n; i++) {
		if (x[i] == '1') {
			mod_1 = mod_1 + mods[0][n - 1 - i];
			mod1 = mod1 + mods[1][n - 1 - i];
		}
	}

	for (ULL i = 0; i < n; i++) {
		if (x[i] == '1') {
			if (cnt0) {
				col(0);
				continue;
			}

			ULL mod0 = (mod_1 - mods[0][n - 1 - i]) % one_1;
			ULL cnt = 1;
			while (mod0 > 0) {
				bitset<32> b(mod0);
				mod0 = mod0 % b.count();
				cnt++;
			}

			col(cnt);
		}
		else {
			ULL mod0 = (mod1 + mods[1][n - 1 - i]) % one1;
			ULL cnt = 1;
			while (mod0 > 0) {
				bitset<32> b(mod0);
				mod0 = mod0 % b.count();
				cnt++;
			}

			col(cnt);
		}
	}

	return 0;
}
