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
template<typename T> using VP = vector<pair<T, T>>;

const double PI = 3.141592653589793;
const int MOD = 1000000007;
const LL INF64 = INT64_MAX >> 1;
const int INF = INT_MAX >> 1;

template<typename T> inline void upsort(vector<T>& x) { sort(x.begin(), x.end()); }
template<typename T> inline void downsort(vector<T>& x) { sort(x.begin(), x.end(), greater<T>()); }
template<typename T> inline void col(T x) { cout << x << '\n'; }
template<> inline void col(double x) { cout << fixed << setprecision(12) << x << '\n'; }
#pragma endregion

template<typename T> struct edge { T u, v, cost; };
template<typename T> std::vector<T> BellmanFord(const T start, const T V, const std::vector<edge<T>>& es) {
	using namespace std;
	constexpr T inf = numeric_limits<T>::max() >> 1;
	vector<T> mincost(V, inf); // i番目のノードまでの最小コスト
	mincost[start] = 0;
	T i = 0;
	// 負の閉路が存在しなければ更新回数は高々 V-1回
	while (i++ < V) {
		bool update = false;
		for (auto& e : es) {
			if (mincost[e.u] != inf && mincost[e.v] > mincost[e.u] + e.cost) {
				mincost[e.v] = mincost[e.u] + e.cost;
				update = true;
				 if (i == V) return vector<T>(); // 負の閉路検出（サイズ0のvectorを返す）
			}
		}
		if (!update) break;
	}
	return mincost;
}

signed main()
{
	constexpr int inf = numeric_limits<int>::max() >> 1;
	int V, E, r;
	cin >> V >> E >> r;
	vector<edge<int>> es(E);
	for (auto& e : es) cin >> e.u >> e.v >> e.cost;

	vector<int> mincost = BellmanFord(r, V, es);

	if (mincost.size()) {
		for (auto& c : mincost) {
			if (c == inf) cout << "INF\n";
			else cout << c << '\n';
		}
	}
	else cout << "NEGATIVE CYCLE\n";

	return 0;
}
