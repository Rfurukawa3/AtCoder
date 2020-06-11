#include <vector>

// Union-Find木
template<typename T> struct UnionFind {
    std::vector<T> par;
    std::vector<T> rank;

    // n要素で初期化
    UnionFind(T n) {
        par = std::vector<T>(n);
        for (T i = 0; i < n; i++) par[i] = i;
        rank = std::vector<T>(n, 0);
    }

    // 木の根を求める
    T find(T x) {
        if (par[x] == x) return x;
        else return par[x] = find(par[x]);
    }

    // xとyの属する集合を併合
    void unite(T x, T y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (rank[x] < rank[y]) {
            par[x] = y;
        }
        else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }

    // xとyが同じ集合に属するかどうか
    bool same(T x, T y) {
        return find(x) == find(y);
    }
};

// pairの3要素版
template<typename T> struct trio {
	T a, b, c;

	trio(): a(0), b(0), c(0){}
	trio(T a, T b, T c) : a(a), b(b), c(c) {}
	trio(const trio& obj) : a(obj.a), b(obj.b), c(obj.c) {}

	trio operator = (const trio& obj) {
		this->a = obj.a;
		this->b = obj.b;
		this->c = obj.c;
		return *this;
	}
	bool operator == (const trio& obj) { return (this->a == obj.a) && (this->b == obj.b) && (this->c == obj.c); }
	bool operator != (const trio& obj) { return !(*this == obj); }
	bool operator < (const trio& obj) {
		if (this->a == obj.a) {
			if (this->b == obj.b) return this->c < obj.c;
			return this->b < obj.b;
		}
		return this->a < obj.a;
	}
	bool operator > (const trio& obj) {
		if (this->a == obj.a) {
			if (this->b == obj.b) return this->c > obj.c;
			return this->b > obj.b;
		}
		return this->a > obj.a;
	}
	bool operator <= (const trio& obj) { return !(*this > obj); }
	bool operator >= (const trio& obj) { return !(*this < obj); }
};

