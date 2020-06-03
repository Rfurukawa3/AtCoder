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

// エラトステネスの篩
template<typename T> void Eratosthenes(const T N, std::vector<T>& prime) {
    std::vector<bool> is_prime(N + 1, true);
    for (T i = 2; i <= N; i++) {
        if (is_prime[i]) {
            for (T j = 2 * i; j <= N; j += i) is_prime[j] = false;
            prime.emplace_back(i);
        }
    }
}

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
