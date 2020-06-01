#include <iostream>
#include <vector>
#include <stack>

// nCk = n−1Ck−1 + n−1Ck（パスカルの三角形）を利用した組み合わせ計算関数
template<typename T> T combination(T N, T K) {
	if (N < K) return 0;
	if (N == K || K == 0) return 1;
	vector<T> v(N, 1);
	T prev1 = 1, prev2 = 1; // prev1 = n−1Ck−1, prev2 = n−1Ck

	for (T n = 2; n <= N; n++) {
		prev1 = 1;
		T k = 1;
		while (k < n && k <= K) {
			prev2 = v[k];
			v[k++] = prev1 + prev2;
			//v[k++] = (prev1 + prev2) % MOD; // 余りを答えるように要求された時用
			prev1 = prev2;
		}
	}
	return v[K];
}

// n種類のものから重複を許してr個選ぶ時の全パターンを辞書順に生成する
// n >= 2, r >= 2 を想定しているのでn=1とかは例外処理が必要
bool combination_repetition(int n, int r, std::vector<int>& idx, std::stack<std::pair<int,int>>& rn_st) {
	using namespace std;
	if (idx.empty()) {
		idx = vector<int>(r, 0);
		rn_st.push(make_pair(0, 0));
	}
	else if (rn_st.empty()) {
		if(*idx.begin() == n-1) return false;
		if (*(idx.end()-1) == 0) rn_st.push(make_pair(0, 0));
		else rn_st.push(make_pair(0, *idx.begin() + 1));
	}

	pair<int, int> r_n;
	while (true) {
		r_n = rn_st.top();
		rn_st.pop();
		idx[r_n.first] = r_n.second;
		if (r_n.first >= r-1) break;
		for (int i = n-1; i >= r_n.second; i--) {
			rn_st.push(make_pair(r_n.first + 1, i));
		}
	}
	return true;
}

// n種類のものからr個選ぶ時の全パターンを辞書順に生成する
// n >= 2, r >= 2, n > r を想定しているのでn=rとかは例外処理が必要
bool combination(int n, int r, std::vector<int>& idx, std::stack<std::pair<int, int>>& rn_st) {
	using namespace std;
	if (idx.empty()) {
		idx = vector<int>(r, 0);
		rn_st.push(make_pair(0, 0));
	}
	else if (rn_st.empty()) {
		if (*idx.begin() == n - r) return false;
		if (*(idx.end() - 1) == 0) rn_st.push(make_pair(0, 0));
		else rn_st.push(make_pair(0, *idx.begin() + 1));
	}

	pair<int, int> r_n;
	while (true) {
		r_n = rn_st.top();
		rn_st.pop();
		idx[r_n.first] = r_n.second;
		if (r_n.first >= r - 1) break;
		for (int i = n - r + r_n.first + 1; i > r_n.second; i--) {
			rn_st.push(make_pair(r_n.first + 1, i));
		}
	}
	return true;
}

signed main()
{	
	using namespace std;
	vector<char> sample = { 'a','b','c','d','e' }; // 選択肢を入れた配列

	cout << "重複あり組み合わせ" << endl;
	vector<int> idx1;
	stack<pair<int, int>> rn_st1;
    // 最後の組み合わせになったらfalseを返すのでwhileループで全パターン生成できる
	while (combination_repetition(5, 3, idx1, rn_st1)){
		for(auto& i : idx1) {
            // 選択肢を入れた配列の引数にidxを順番に与えることで一つの選び方が得られる
			cout<< sample[i] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "重複なし組み合わせ" << endl;
	vector<int> idx2;
	stack<pair<int, int>> rn_st2;
	while (combination(5, 3, idx2, rn_st2)) {
		for (auto& i : idx2) {
			cout << sample[i] << ' ';
		}
		cout << endl;
	}

	return 0;
}