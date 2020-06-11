#include <queue>

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