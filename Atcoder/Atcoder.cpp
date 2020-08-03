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

signed main() {
	LL n, k;
	cin >> n >> k;
	map<LL, LL> logs;
	REP(i, n) {
		LL a;
		cin >> a;
		if (logs.find(a) == logs.end()) {
			logs[a] = 1;
		}
		else {
			logs[a]++;
		}
	}

	while (k > 0) {
		auto itr = logs.rbegin();
		k -= (*itr).second;
		if(k<0){
			col((*logs.rbegin()).first);
			return 0;
		}

		LL len = (*itr).first / 2.0;
		LL num = (*itr).second * 2;
		logs.erase((*itr).first);

		if (logs.find(len) == logs.end()) {
			logs[len] = num;
		}
		else {
			logs[len] += num;
		}
	}

	col((*logs.rbegin()).first);
	return 0;
}