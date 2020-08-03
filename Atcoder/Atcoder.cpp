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

LL n, k;
V<LL> a;

template<typename T> bool judge(T x) {
	bool ans;

	LL cnt = 0;
	RBF(i, a) {
		LL tmp = ceil(static_cast<double>(i) / x) - 1;
		cnt += tmp;
	}
	if (cnt > k) {
		ans = false;
	}
	else {
		ans = true;
	}

	return ans;
}
// 範囲[a, b]の連続する整数のなかで，judge(x)=trueとなる最小のxを二分探索で求める
template<typename T> T bin_search_min(T a, T b) {
	if (a > b) {
		return bin_search_min(b, a);
	}

	T x = b;
	T d = max(static_cast<T>(1), (b - a) / 2 + (b - a) % 2);
	T cnt = 0;
	T lim = log2(b - a) + 10;

	while (cnt < lim) {
		if (judge(x)) {
			x -= d;
		}
		else {
			x += d;
		}
		if (x < a) {
			x = a;
			if (judge(x)) {
				break;
			}
		}
		if (x > b) {
			x = b;
			if (!judge(x)) {
				break;
			}
		}
		d = d / 2 + d % 2;
		cnt++;
	}

	if (x < a) {
		x = a;
	}
	while(!judge(x) && x <= b) {
		x++;
	}

	// x > bならjudge(x)=trueとなるxが存在しなかったことを意味する
	return x;
}

signed main() {
	cin >> n >> k;
	a = V<LL>(n);
	LL b = 0;
	REP(i, n) {
		LL tmp;
		cin >> tmp;
		a[i] = tmp;
		b = max(b, tmp);
	}

	LL ans = bin_search_min(1ll, b);
	col(ans);
	return 0;
}