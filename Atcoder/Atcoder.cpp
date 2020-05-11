#pragma region Template
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define rng(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define rbf(i, v) for (auto& (i) : (v))
#define All(x) (x).begin(),(x).end()
#define COL(x) cout << x << endl
#define CO(x) cout << x
//#define int long long

using LL = long long;
using UL = unsigned long;
using ULL = unsigned long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VLL = vector<LL>;
using VS = vector<string>;
using VP = vector<PII>;

const double PI = 3.141592653589793;
const int MOD = 1000000007;
const LL INF64 = INT64_MAX >> 1;
const int INF = INT_MAX >> 1;

inline int sqr(int x) { return (x * x); }
inline void printd(double x) { printf("%.10lf\n", x); }
inline void upsort(VI& x) { sort((x).begin(), (x).end()); }
inline void downsort(VI& x) { sort((x).begin(), (x).end(), greater<int>()); }
inline int absdiff(int a, int b) { return (a - b) * (static_cast<int>(a > b)*2 - 1); }
int gcd(int a, int b) { // 最大公約数
	if (a < b) return gcd(b, a);
	int r;
	while ((r = a % b)) {
		a = b;
		b = r;
	}
	return b;
}
inline int lcm(int a, int b) { return a * b / gcd(a, b); } // 最小公倍数
#pragma endregion

signed main()
{

	return 0;
}