
template<typename T> bool judge(T x) {
	bool ans;

	return ans;
}
// 範囲[a, b]の連続する整数のなかで，judge(x)=trueとなる最小のxを二分探索で求める
template<typename T> T bin_search_min(T a, T b) {
	if (a > b) {
		return bin_search_min(b, a);
	}

	T x = (b - a) / 2;
	T d = std::max(static_cast<T>(1), (b - a) / 4);
	T cnt = 0;
	T lim = log2(b - a) + 10;

	while (cnt < lim) {
		if (judge(x)) {
			x -= d;
		}
		else {
			x += d;
		}
		d = std::max(static_cast<T>(1), d / 2);
		cnt++;
	}

	if (x < a) {
		x = a;
	}
	while(!judge(x) && x <= b) {
		x++;
	}

	// x > bならjudge(x)=trueとなるxが存在しなかったことを意味する
	return x;
}
