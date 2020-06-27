#include <cmath>
#include <vector>

// 差の絶対値
template<typename T> inline T absdiff(T a, T b) { return (a - b) * (static_cast<T>(a > b) * 2 - 1); }

// 最大公約数
template<typename T> T gcd(T a, T b) { 
	if (a < b) return gcd(b, a);
	T r;
	while ((r = a % b)) {
		a = b;
		b = r;
	}
	return b;
}
// 最小公倍数
template<typename T> inline T lcm(T a, T b) { return a * b / gcd(a, b); }

// numを素因数分解してprime_factorに結果を格納する
template<typename T> void prime_factorization(T num, std::vector<std::pair<T, T>>& prime_factor) {
	T L = static_cast<T>(ceil(sqrt(num)));
	for (T x = 2; x <= L; x++) {
		bool flg = false;
		while (num % x == 0) {
			if (flg) prime_factor.back().second++;
			else prime_factor.emplace_back(make_pair(x, 1));
			flg = true;
			num /= x;
		}
		if (num == 1) break;
	}
	if (num > 1) prime_factor.emplace_back(make_pair(num, 1));
}
// 素数リストあり
template<typename T> void prime_factorization(T num, std::vector<std::pair<T, T>>& prime_factor, const std::vector<T>& prime) {
	for (auto& x : prime) {
		bool flg = false;
		while (num % x == 0) {	
			if (flg) prime_factor.back().second++;
			else prime_factor.emplace_back(make_pair(x, 1));
			flg = true;
			num /= x;
		}
		if (num == 1) break;
	}
}

// エラトステネスの篩
// [0, N]の範囲の素数をリスト化
std::vector<bool> is_prime;
std::vector<int> prime;
template<typename T> void Eratosthenes(const T N) {
    if (N < 2) {
        is_prime = std::vector<bool>(N + 1, false);
        prime = std::vector<T>();
        return;
    }
    is_prime = std::vector<bool>(N + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    prime = std::vector<T>();
    T lim = ceil(sqrt(N));
    for (T i = 2; i <= lim; i++) {
        if (is_prime[i]) {
            for (T j = i * i; j <= N; j += i) is_prime[j] = false;
            prime.emplace_back(i);
        }
    }
    for (T i = lim + 1; i <= N; i++) {
        if (is_prime[i]) prime.emplace_back(i);
    }
}

// 区間篩
// 区間[a, b)の素数を求める, bは含まない
std::vector<bool> is_prime;
std::vector<int> prime;
template<typename T> void segment_sieve(const T a, const T b) {
    prime = std::vector<T>();
    if (a >= b) {
        is_prime =  std::vector<bool>();
        return;
    }
    T lim = ceil(sqrt(b));
    is_prime = std::vector<bool>(b - a, true); // is_prime[i-a] = true ⇔ iが素数
    std::vector<bool> is_prime_small(lim, true);
    for (T i = 2; i < lim; i++) {
        if (is_prime_small[i]) {
            for (T j = i * i; j < lim; j += i) is_prime_small[j] = false; // [2, √b)の篩
            for (T j = std::max(i, (a + i - 1) / i) * i; j < b; j += i) is_prime[j] = false; // [a, b)の篩
        }
    }
    for (T i = 0; i < b - a; i++) {
        if (is_prime[i]) prime.emplace_back(i + a);
    }
}

// 拡張ユークリッドの互除法
// ax + by = gcd(a, b) を解く
template<typename T> T extgcd(T a, T b, T& x, T& y) {
    T d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else {
        x = 1; y = 0;
    }
    return d;
}

// 繰り返し二乗法
// x^22 = x^(2^4) * x^(2^2) * x^(2^1)のように見なすことで高速にべき乗を計算する（22は2進数で10110）
template<typename T> T mod_pow(T x, T n, T mod) {
    T res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod; // 最下位ビットが立っているときにx^(2^i)をかける
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// エラトステネスの篩(高速版)
// https://qiita.com/peria/items/54499b9ce9d5c1e93e5a
std::vector<unsigned char> is_prime;
std::vector<int> prime;
template<typename T> void Eratosthenes(const T N) {
    if (N < 2) {
        prime = std::vector<T>();
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
    is_prime = std::vector<UC>(N / 30 + 1, 255u); 
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
