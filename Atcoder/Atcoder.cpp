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
const LL INF64 = static_cast<LL>(1e18) + 2;
const int INF = static_cast<int>(1e9) + 2;

template<typename T> inline void upsort(vector<T>& x) { sort(x.begin(), x.end()); }
template<typename T> inline void downsort(vector<T>& x) { sort(x.begin(), x.end(), greater<T>()); }
template<typename T> inline void col(T x) { cout << x << '\n'; }
template<> inline void col(double x) { cout << fixed << setprecision(12) << x << '\n'; }
#pragma endregion

signed main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}

	int ans = 0;
	vector<bool> seen(n, false);
	for (int i = 0; i < n; i++)
	{
		if (!seen[i]) {
			// first := 現在のノード, second := 直前に訪問したノード
			stack<pair<int,int>> st;
			st.push({ i,-1 });
			seen[i] = true;
			bool roop = false;

			while (!st.empty()) {
				int now = st.top().first, prev = st.top().second;
				st.pop();

				for (auto& gi : g[now]) {
					if (!seen[gi]) {
						st.push({ gi, now });
						seen[gi] = true;
					}
					else {
						// 直前に訪問したわけでもないのに訪問済だったら閉路が存在する
						if (gi != prev) roop = true;
					}
				}
			}

			if (!roop) ans++;
		}
	}

	cout << ans << endl;
	return 0;
}
