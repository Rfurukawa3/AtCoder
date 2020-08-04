
template<typename T> bool judge(T x) {
	bool ans;

	return ans;
}

// 範囲[a, b]の連続する整数のなかで，judge()=trueとなる最小の値を二分探索で求める
// ok > bならjudge()=trueとなる値が存在しなかったことを意味する
template<typename T> T bin_search_min(T a, T b) {
	T ng = a - 1, ok = b + 1;
	while (ok - ng > 1) {
		T mid = (ng + ok) / 2;
		if (judge(mid)) {
			ok = mid;
		}
		else {
			ng = mid;
		}
	}
	return ok;
}

// 範囲[a, b]の連続する整数のなかで，judge(x)=trueとなる最大のxを二分探索で求める
// ok < aならjudge()=trueとなる値が存在しなかったことを意味する
template<typename T> T bin_search_max(T a, T b) {
	T ok = a - 1, ng = b + 1;
	while (ng - ok > 1) {
		T mid = (ng + ok) / 2;
		if (judge(mid)) {
			ok = mid;
		}
		else {
			ng = mid;
		}
	}
	return ok;
}
