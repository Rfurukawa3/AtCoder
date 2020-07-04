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
	int n, k;
	string s;
	cin >> n >> k >> s;
	string smin(s), t(n, '.');
	sort(smin.begin(), smin.end());

	int k0 = 0;
	for (int i = 0; i < n; i++) { // t[i]を決める
		for (int j = 0; j < n; j++) { // t[i]に入れる文字を小さい順に検証
			if (smin[j] == '.') continue; // 使用済みか否かをチェック

			// ktmp := t[i] = smin[j] とした時の最小の不一致数
			int ktmp = k0;
			if (s[i] != smin[j]) ktmp++;

			// 未使用の文字がs[i+1]以降の文字列と何文字一致させられるか調べる
			// abc1 := s[i+1]以降の文字列における各アルファベットの登場回数
			// abc2 := 未使用の文字における各アルファベットの登場回数
			vector<int> abc1(26, 0), abc2(26, 0);
			for (int m = i+1; m < n; m++) {
				abc1[s[m] - 'a']++;
			}
			for (int m = 0; m < n; m++) {
				if (smin[m] == '.' || m == j) continue;
				abc2[smin[m] - 'a']++;
			}
			int match = 0;
			for (int m = 0; m < 26; m++) {
				// abc1[0]=2, abc2[0]=4 の時、'a'2文字分は一致させられる
				match += min(abc1[m], abc2[m]);
			}

			ktmp += n - i - 1 - match;
			if (ktmp <= k) {
				if (s[i] != smin[j]) k0++;
				t[i] = smin[j];
				smin[j] = '.';
				break;
			}
		}
	}

	cout << t << endl;
	return 0;
}
