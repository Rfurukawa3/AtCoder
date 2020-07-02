#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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
// n, r が自然数であることが前提
// idxは空のオブジェクトを渡す
std::stack<std::pair<int, int>> rn_st;
bool combination_repetition(int n, int r, std::vector<int>& idx) {
	using namespace std;
	bool flg = false;
	if (idx.empty()) {
		idx = vector<int>(r, 0);
		rn_st = stack<pair<int, int>>();
		rn_st.push(make_pair(0, 0));
		flg = true;
	}
	else if (rn_st.empty()) {
		if(*idx.begin() == n-1) return false;
		if (*(idx.end()-1) == 0) rn_st.push(make_pair(0, 0));
		else rn_st.push(make_pair(0, *idx.begin() + 1));
	}

	if(n == 1) {
		rn_st.pop();
		for(int i = 0; i < r; i++) idx[i] = 0;
	}
	else if(r == 1) {
		if (flg){
			rn_st.pop();
			int i = n;
			while(i > 0) {
				rn_st.push(make_pair(0, --i));
			}
		}
		pair<int, int> r_n;
		r_n = rn_st.top();
		rn_st.pop();
		idx[r_n.first] = r_n.second;
	}
	else{
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
	}

	return true;
}

// n種類のものからr個選ぶ時の全パターンを辞書順に生成する
// n >= r かつ n, r が自然数であることが前提
// idxは空のオブジェクトを渡す
std::stack<std::pair<int, int>> rn_st;
bool combination(int n, int r, std::vector<int>& idx) {
	using namespace std;
	bool flg = false;
	if (idx.empty()) {
		idx = vector<int>(r, 0);
		rn_st = stack<pair<int, int>>();
		rn_st.push(make_pair(0, 0));
		flg = true;
	}
	else if (rn_st.empty()) {
		if (*idx.begin() == n - r) return false;
		if (*(idx.end() - 1) == 0) rn_st.push(make_pair(0, 0));
		else rn_st.push(make_pair(0, *idx.begin() + 1));
	}

	if(n == r){
		rn_st.pop();
		for(int i = 0; i < r; i++) idx[i] = i;
	}
	else if(r == 1){
		if (flg){
			rn_st.pop();
			int i = n;
			while(i > 0) {
				rn_st.push(make_pair(0, --i));
			}
		}
		pair<int, int> r_n;
		r_n = rn_st.top();
		rn_st.pop();
		idx[r_n.first] = r_n.second;
	}
	else{
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
	}
	return true;
}

// n個からr個選んで並べる時の全パターンを順に生成する
// 上のcombination() が必要
std::vector<int> idx_c;
bool permutation(int n, int r, std::vector<int>& idx) {
	using namespace std;
	if (idx.empty()) {
		idx_c = vector<int>();
		combination(n, r, idx_c);
		idx = idx_c;
		return true;
	}
	if (next_permutation(idx.begin(), idx.end())) {
		return true;
	}
	if (combination(n, r, idx_c)) {
		idx = idx_c;
		return true;
	}
	return false;
}

signed main()
{	
	using namespace std;
	vector<char> sample = { 'a','b','c','d','e' }; // 選択肢を入れた配列

	cout << "重複あり組み合わせ" << endl;
	vector<int> idx1;
    // 最後の組み合わせになったらfalseを返すのでwhileループで全パターン生成できる
	while (combination_repetition(5, 3, idx1)){
		for(auto& i : idx1) {
            // 選択肢を入れた配列の引数にidxを順番に与えることで一つの選び方が得られる
			cout<< sample[i] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << "重複なし組み合わせ" << endl;
	vector<int> idx2;
	while (combination(5, 3, idx2)) {
		for (auto& i : idx2) {
			cout << sample[i] << ' ';
		}
		cout << endl;
	}

	cout << "順列" << endl;
	vector<int> idx3;
	while (permutation(5, 3, idx3)) {
		for (auto& i : idx3) {
			cout << sample[i] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	return 0;
}