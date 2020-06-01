#include <cmath>
#include <vector>

// 差の絶対値
template<typename T> inline T absdiff(T a, T b) { return (a - b) * (static_cast<T>(a > b) * 2 - 1); }

// numを素因数分解してprime_factorに結果を格納する
template<typename T> void prime_factorization(T num, std::vector<std::pair<T, T>>& prime_factor) {
	using namespace std;
	T L = static_cast<T>(ceil(sqrt(num))), i = 0;
	prime_factor = vector<pair<T, T>>(L, make_pair(0, 0));
	for (T x = 2; x <= L; x++) {
		while (num % x == 0) {
			if (prime_factor[i].first) prime_factor[i].second++;
			else prime_factor[i] = make_pair(x, 1);
			num /= x;
		}
		if (num == 1) break;
		if (prime_factor[i].first) i++;
	}
	if (num > 1) prime_factor[i] = make_pair(num, 1);
}

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