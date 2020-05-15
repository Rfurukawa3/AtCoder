#pragma region Template
//#include <bits/stdc++.h>
//using namespace std;

//#define rep(i, n) for (int (i) = 0; (i) < (n); (i)++)
//#define rng(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
//#define rbf(i, v) for (auto& (i) : (v))
//#define All(x) (x).begin(),(x).end()
//#define COL(x) cout << x << endl
//#define CO(x) cout << x
////#define int long long
//
//using LL = long long;
//using UL = unsigned long;
//using ULL = unsigned long long;
//using PII = pair<int, int>;
//using VI = vector<int>;
//using VVI = vector<VI>;
//using VLL = vector<LL>;
//using VS = vector<string>;
//using VP = vector<PII>;
//
//const double PI = 3.141592653589793;
//const int MOD = 1000000007;
//const LL INF64 = INT64_MAX >> 1;
//const int INF = INT_MAX >> 1;
//
//inline int sqr(int x) { return (x * x); }
//inline void printd(double x) { printf("%.10lf\n", x); }
//inline void upsort(VI& x) { sort((x).begin(), (x).end()); }
//inline void downsort(VI& x) { sort((x).begin(), (x).end(), greater<int>()); }
//inline int absdiff(int a, int b) { return (a - b) * (static_cast<int>(a > b)*2 - 1); }
//int gcd(int a, int b) { // 最大公約数
//	if (a < b) return gcd(b, a);
//	int r;
//	while ((r = a % b)) {
//		a = b;
//		b = r;
//	}
//	return b;
//}
//inline int lcm(int a, int b) { return a * b / gcd(a, b); } // 最小公倍数
#pragma endregion

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

template<typename T> T combination(T N, T K) {
	if (N < K) return 0;
	if (N == K || K == 0) return 1;
	vector<T> v(N, 1);
	T prev1 = 1, prev2 = 1; // prev1 = n−1Ck−1, prev2 = n−1Ck

	for (T n = 2; n <= N; n++) {
		prev1 = 1;
		T k = 1;
		while (k < n && k <= K) {
			prev2 = v[k];
			v[k++] = (prev1 + prev2) % MOD; // 余りを答えるように要求された時用
			prev1 = prev2;
		}
	}
	return v[K];
}

signed main()
{
	using ULL = unsigned long long;
	ULL N, M;
	cin >> N >> M;

	// Mを素因数分解
	ULL L = static_cast<ULL>(ceil(sqrt(M))), i = 0;
	vector<pair<ULL, ULL>> prime(L, make_pair(0,0));
	for (ULL x = 2; x <= L; x++) {
		while (M % x == 0) {
			if (prime[i].first) prime[i].second++;
			else prime[i] = make_pair(x, 1);
			M /= x;
		}
		if (M == 1) break;
		if (prime[i].first) i++;
	}
	if (M > 1) prime[i] = make_pair(M, 1);

	// 素因数ごとに重複組合せで振り分け
	ULL comb = 1;
	for (auto& p : prime) {
		if (p.first == 0) break;
		comb = (comb * combination(p.second + N - 1, p.second)) % MOD;
	}

	cout << comb << endl;
	return 0;
}