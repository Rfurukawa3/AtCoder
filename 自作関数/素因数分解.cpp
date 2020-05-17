#include <cmath>
#include <vector>

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
