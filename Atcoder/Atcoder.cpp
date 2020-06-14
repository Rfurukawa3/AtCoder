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

template<typename T> void Eratosthenes(const T N, std::vector<T>& prime) {
    std::vector<bool> is_prime(N + 1, true);
    for (T i = 2; i <= N; i++) {
        if (is_prime[i]) {
            for (T j = 2 * i; j <= N; j += i) is_prime[j] = false;
            prime.emplace_back(i);
        }
    }
}

signed main()
{
    const int yn = 200000;
    int n, q;
    cin >> n >> q;
    V<priority_queue<int>> you(yn);
    VP<int> enji(n);
    VV<int> del(yn);
    REP(i, n) {
        int a, b;
        cin >> a >> b;
        you[b - 1].push(a);
        enji[i] = make_pair(a, b - 1);
    }
    priority_queue<int, V<int>, greater<int>> byo;

    RBF(y, you) {
        if (!y.empty()) {
            byo.push(y.top());
        }
    }

    REP(i, q) {
        int c, d;
        cin >> c >> d;
        c--; d--;
        del[enji[c].second].emplace_back(enji[c].first);
        if (enji[c].first == byo.top()) byo.pop();
        you[d].push(enji[c].first);

    }

    return 0;
}
