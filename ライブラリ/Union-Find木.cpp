#include <vector>

template<typename T> class UnionFind {
public:
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