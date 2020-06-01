#pragma region Template
#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i = 0; i < n; i++)
#define RNG(i, a, b) for(int i = a; i < b; i++)
#define RBF(i, v) for(auto& i : v)
#define ALL(x) x.begin(), x.end()

using LL = long long;
using UL = unsigned long;
using ULL = unsigned long long;
template<typename T> using P = pair<T, T>;
template<typename T> using V = vector<T>;
template<typename T> using VV = vector<V<T>>;

const double PI = 3.141592653589793;
const int MOD = 1000000007;
const LL INF64 = INT64_MAX >> 1;
const int INF = INT_MAX >> 1;

template<typename T> inline void upsort(vector<T>& x) { sort(x.begin(), x.end()); }
template<typename T> inline void downsort(vector<T>& x) { sort(x.begin(), x.end(), greater<T>()); }
template<typename T> inline void col(T x) { cout << x << endl; }
template<typename T> inline void co(T x) { cout << x; }
inline void printd(double x) { printf("%.10lf\n", x); }
#pragma endregion

signed main()
{
	return 0;
}
