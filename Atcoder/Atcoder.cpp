#pragma region Template
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
#pragma endregion

signed main()
{
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (auto& ai : a) cin >> ai;
	for (auto& bi : b) cin >> bi;
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	vector<int> b0(b);

	int win = 0, all = 0;
	do {
		b = b0;
		do {
			int awin = 0, bwin = 0;
			for (int i = 0; i < n; i++) {
				if (a[i] > b[i]) awin++;
				else bwin++;
			}
			if (awin > bwin) win++;
			all++;
		} while (next_permutation(b.begin(), b.end()));
	} while (next_permutation(a.begin(), a.end()));

	cout << static_cast<double>(win) / all << '\n';
	return 0;
}
