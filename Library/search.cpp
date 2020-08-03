
template<typename T> bool judge(T x) {
	bool ans;

	return ans;
}

// 範囲[a, b]の連続する整数のなかで，judge(x)=trueとなる最小のxを二分探索で求める
template<typename T> T bin_search_min(T a, T b) {
	if (a > b) {
		return bin_search_min(b, a);
	}

	T x = b;
	T d = max(static_cast<T>(1), (b - a) / 2 + (b - a) % 2);
	T cnt = 0;
	T lim = log2(b - a) + 10;

	while (cnt < lim) {
		if (judge(x)) {
			x -= d;
		}
		else {
			x += d;
		}
		if (x < a) {
			x = a;
			if (judge(x)) {
				break;
			}
		}
		if (x > b) {
			x = b;
			if (!judge(x)) {
				break;
			}
		}
		d = d / 2 + d % 2;
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

// 範囲[a, b]の連続する整数のなかで，judge(x)=trueとなる最大のxを二分探索で求める
template<typename T> T bin_search_max(T a, T b) {
	if (a > b) {
		return bin_search_min(b, a);
	}

	T x = a;
	T d = max(static_cast<T>(1), (b - a) / 2 + (b - a) % 2);
	T cnt = 0;
	T lim = log2(b - a) + 10;

	while (cnt < lim) {
		if (judge(x)) {
			x += d;
		}
		else {
			x -= d;
		}
		if (x < a) {
			x = a;
			if (!judge(x)) {
				break;
			}
		}
		if (x > b) {
			x = b;
			if (judge(x)) {
				break;
			}
		}
		d = d / 2 + d % 2;
		cnt++;
	}

	if (x > b) {
		x = b;
	}
	while(!judge(x) && x >= a) {
		x--;
	}

	// x < aならjudge(x)=trueとなるxが存在しなかったことを意味する
	return x;
}
