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

template<typename T> void Eratosthenes(const T N, std::vector<T>& prime) {
    std::vector<bool> is_prime(N + 1, true);
    T imax = static_cast<T>(ceil(sqrt(static_cast<double>(N))));
    for (T i = 2; i <= imax; i++) {
        if (is_prime[i]) {
            for (T j = i * i; j <= N; j += i) is_prime[j] = false;
            prime.emplace_back(i);
        }
    }

    for (T i = imax+1; i <= N; i++) {
        if (is_prime[i]) prime.emplace_back(i);
    }

}

template<typename T> void fastEratosthenes(const T N, std::vector<T>& prime) {
    if (N < 2) {
        return;
    }
    if (N < 3) {
        prime = std::vector<T>{ 2 };
        return;
    }
    if (N < 5) {
        prime = std::vector<T>{ 2,3 };
        return;
    }
    if (N < 7) {
        prime = std::vector<T>{ 2,3,5 };
        return;
    }
    prime = std::vector<T>{ 2,3,5 };

    // 2,3,5の倍数を排除した30k + {1,7,11,13,17,19,23,29} について篩をかける
    using UC = unsigned char;
    const std::vector<T> m{ 1,7,11,13,17,19,23,29 };
    std::vector<UC> is_prime(N / 30 + 1, 255u); 
    is_prime[0]--; 
    T kmax = static_cast<T>(ceil((sqrt(static_cast<double>(N)) - 29.0) / 30.0));

    std::vector<T> mm_30(64); // [m_i*m_j+1/30] - [m_i*m_j/30] を保持する配列
    std::vector<T> m_m(8); // m_j+1 - m_jを保持する配列
    std::vector<UC> masks(64); // mi*mj%30 = {1,7,11,13,17,19,23,29}の該当ビットを外すビットマスク
    std::map<T, UC> mmap; // {1,7,11,13,17,19,23,29}のそれぞれに対応するビットマスク
    UC ibit = 1u;
    for (auto& mi : m) {
        mmap.insert(std::make_pair(mi, ~ibit));
        ibit = ibit << static_cast<UC>(1u);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            masks[8 * i + j] = mmap.at((m[i] * m[j]) % 30);

            if (j < 7) mm_30[8 * i + j] = m[i] * m[j + 1] / 30 - m[i] * m[j] / 30;
            else mm_30[8 * i + j] = m[i] * m[0] / 30 - m[i] * m[j] / 30 + m[i];
        }
        if (i < 7) m_m[i] = m[i + 1] - m[i];
        else m_m[i] = m[0] - m[i] + 30;
    }
    
    for (T k = 0; k <= kmax; k++) {
        if (is_prime[k]) {
            ibit = 1u;
            int i = 0;
            while (i < 8) {
                if (is_prime[k] & ibit) {
                    T kj = k * (30 * k + 2 * m[i]) + m[i] * m[i] / 30;
                    UC mask = masks[8 * i + i];
                    int j = i;
                    while (30 * kj < N) {
                        is_prime[kj] &= mask;

                        kj += k * m_m[j] + mm_30[8*i + j];
                        j = (j + 1) % 8;
                        mask = masks[8 * i + j];
                    }

                    if (30 * k + m[i] > N) return;
                    else prime.emplace_back(30 * k + m[i]);
                }
                ibit = ibit << static_cast<UC>(1u);
                i++;
            }
        }
    }

    for (T k = kmax + 1; k < is_prime.size(); k++) {
        if (is_prime[k]) {
            ibit = 1u;
            int i = 0;
            while (i < 8) {
                if (is_prime[k] & ibit) {
                    if (30 * k + m[i] > N) return;
                    else prime.emplace_back(30 * k + m[i]);
                }
                ibit = ibit << static_cast<UC>(1u);
                i++;
            }
        }
    }

}

#include <chrono>

signed main()
{
    std::chrono::system_clock::time_point start, end;

    V<int> prime1, prime2;
    double caltime;
    int N = 7;
    start = std::chrono::system_clock::now();
    Eratosthenes(N, prime1);
    end = std::chrono::system_clock::now();  // 計測終了時間
    caltime = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    col(caltime);

    start = std::chrono::system_clock::now();
    fastEratosthenes(N, prime2);
    end = std::chrono::system_clock::now();  // 計測終了時間
    caltime = (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
    col(caltime);

    col(prime1.size());
    col(prime2.size());

    auto p1 = prime1.begin(), p2 = prime2.begin();
    while (p1 != prime1.end() || p2 != prime2.end()) {
        cout << *p1 << "  " << *p2 << endl;
        p1++; p2++;
    }
    


	return 0;
}
