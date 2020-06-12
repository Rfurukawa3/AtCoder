#include <queue>

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

// 最小全域木（クラスカル法）
// 構造体edge := 辺の情報（u, v := 繋ぐ頂点，cost := 辺のコスト）
// V := 頂点数
template<typename T> struct edge { T u, v, cost; };
template<typename T> T kruskal(std::vector<edge<T>>& es, T V) {
    using namespace std;
    sort(es.begin(), es.end(), [](edge<T>& e1, edge<T>& e2) { return e1.cost < e2.cost; });
    UnionFind<T> uf(V);
    T result = 0;
    for (auto& e : es) {
        if (!uf.same(e.u, e.v)) {
            uf.unite(e.u, e.v);
            result += e.cost;
        }
    }
    return result;
}

// ダイクストラ法
// graph[i]はi番目のノードから繋がるノードとそのコストを格納する std::pair<コスト，ノード>
template<typename T> std::vector<T> Dijkstra(const T start, const T goal, const std::vector<std::vector<std::pair<T,T>>>& graph) {
	using namespace std;
	vector<T> mincost(graph.size(), numeric_limits<T>::max()); // i番目のノードまでの最小コスト
	vector<T> from(graph.size(), 0); // 最短経路を通る場合の一つ前のノード
	vector<bool> done(graph.size(), false); // i番目のノードまでの最短経路が確定したか
	priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> nodes; // 次に最短が確定する候補ノード <コスト，ノード>
	mincost[start] = 0;
	from[start] = -1;
	nodes.push(make_pair(0, start));

	// 各ノードまでの最小コストをダイクストラ法で求めていく
	while (!nodes.empty()) {
		pair<T, T> node = nodes.top();
		nodes.pop();

		if (!done[node.second]) {
			done[node.second] = true;
			for (auto& next : graph[node.second]) {
				T cost = node.first + next.first;
				if (mincost[next.second] > cost) {
					mincost[next.second] = cost;
					from[next.second] = node.second;
					nodes.push(make_pair(cost, next.second));
				}
			}
		}
	}
	//return mincost; // ゴールまでの最小コストを求めるだけならここでreturn

	// ゴールまでの最短経路を得る
	T p = goal;
	vector<T> minRoute(1, goal);
	while (p != start) {
		p = from[p];
		minRoute.emplace_back(p);
	}
	reverse(minRoute.begin(), minRoute.end());
	return minRoute;
}

