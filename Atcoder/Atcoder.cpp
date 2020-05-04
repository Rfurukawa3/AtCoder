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
using ULL = unsigned long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
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
	int N;
	cin >> N;
	VP LR(N);
	int n = 1;
	rbf(lr, LR) {
		int a;
		cin >> a;
		lr = make_pair(n+a, n-a);
		n++;
	}
	sort(All(LR));

	VI L(N);
	rep(i, N) {
		L[i] = LR[i].first;
	}

	double ans = 0.0;
	rbf(lr, LR) {
		int R = lr.second;
		int low = distance(L.begin(), lower_bound(All(L), R));
		int high = distance(L.begin(), upper_bound(All(L), R));
		if (low == N || high == 0) continue;

		if (lr.first >= LR[low].second && lr.first <= LR[high - 1].second) {
			while (low < high) {
				if (lr.first == LR[low++].second) ans += 0.5;
				else ans += 1.0;
			}
		}
		else ans += high - low;
	}

	COL(static_cast<int>(ans));
	return 0;
}