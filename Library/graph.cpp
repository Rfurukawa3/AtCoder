#include <queue>

// Union-Find木
// グループ分け用の木構造
// 同じ集合に属するかの判定と集合の併合機能を持つ
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
// 全域木 := 全ての点が互いに辿り着ける
// 最小全域木 := 全域木の中でコストが最小のもの
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
// ある点から各点への最小コストを求める、負のコストがあったらダメ
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

// ベルマンフォード法
// ある点から各点への最小コストを求める、負のコストがあってもOK
// 負の閉路検出にも
template<typename T> struct edge { T u, v, cost; };
template<typename T> std::vector<T> BellmanFord(const T start, const T V, const std::vector<edge<T>>& es) {
	using namespace std;
	constexpr T inf = numeric_limits<T>::max() >> 1;
	vector<T> mincost(V, inf); // i番目のノードまでの最小コスト
	mincost[start] = 0;
	T i = 0;
	// 負の閉路が存在しなければ更新回数は高々 V-1回
	while (i++ < V) {
		bool update = false;
		for (auto& e : es) {
			if (mincost[e.u] != inf && mincost[e.v] > mincost[e.u] + e.cost) {
				mincost[e.v] = mincost[e.u] + e.cost;
				update = true;
				 if (i == V) return vector<T>(); // 負の閉路検出（サイズ0のvectorを返す）
			}
		}
		if (!update) break;
	}
	return mincost;
}

// ワーシャル-フロイド法
// 全点間の最小コストを求める
// cost[i][j] := iとjをつなぐ辺のコスト，辺がない場合はINF，ただしcost[i][i]=0
template<typename T> void WarshallFloyd(std::vector<std::vector<T>>& cost) {
    const T V = cost.size();
    for (T k = 0; k < V; k++) {
        for (T i = 0; i < V; i++) {
            for (T j = 0; j < V; j++) {
                // 頂点kを経由するかしないかでコストの小さいほうを採用する
                // cost[i][j] := iからjへのコスト
                // cost[i][k] + cost[k][j] := kを経由してiからjへ辿る場合のコスト
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
}
