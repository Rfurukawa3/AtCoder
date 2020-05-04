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
	int N, W;
	cin >> N >> W;
	vector<int> v(N), w(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i] >> w[i];
	}

    // dp[i+1][j] : i番目までの品物から重さjを超えないように選んだときの価値の最大値
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    // 動的計画法
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < W + 1; j++) {
            // そもそもi番目の品物が重量オーバーの場合
            if (w[i] > j) dp[i + 1][j] = dp[i][j];

            // dp[i][j - w[i]]は重さ制限「j - w[i]」の時にi番目の品物を0個以上入れて得た価値
            // 重さ制限がjになった時にi番目の品物を追加するかしないかで比較する
            else dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
        }
    }

    cout << dp[N][W] << endl;
	return 0;
}